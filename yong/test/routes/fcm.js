var exec =require('child_process').exec,
child;
const express = require('express');
const router = express.Router();
const arp =require('node-arp');
const pool = require('../config/db_pool');
const FCM = require('fcm-push');
const requestIp=require('request-ip');
const convert=require('convert-string');
var dnsSync = require('dns-sync');
const serverKey = require('../config/serverKey').serverKey;
var fcm = new FCM(serverKey);

    router.post('/', async(req, res)=>{
        try{
            var connection = await pool.getConnection();
            let query = 'select deviceToken from admin';
            let writer = await connection.query(query);
            var dns=req.body.dns;
            console.log(dns);
       
            ip=requestIp.getClientIp(req);
         ip=JSON.stringify(ip);
         ip= ip.substring(8,ip.length-1);
         console.log(ip);
        
         //알람부르기 & 메세지전송 & 저장
              var message = {
                  to: writer[0].deviceToken , // required fill with device token or topics
                  notification: {
                      title: '요청',
                      body: '차단해제요청이 왔습니다.'
                  }
              };
              let query2 = 'insert into blocklist set ?';
              let record2 = {
                "dns" : req.body.dns,
                "ip" : ip
              };
              await connection.query(query2, record2);
        
              console.log(serverKey);
              fcm.send(message)
                .then(function(response){
                    console.log(message);
                    console.log("Successfully sent with response: ", response);
                })
                .catch(function(err){
                    console.log("Something has gone wrong!");
                    console.error(err);
                });
       
           res.status(200).send({"message": "Succeed in inserting comment."});
          
        } catch(err){
          console.log(err);
          res.status(500).send({
            "message": "syntax error"
          });
        } finally{
          pool.releaseConnection(connection);
        }
      });
      router.get('/', async function (req, res) {
        try {
          var connection = await pool.getConnection();
       
          let query='select ddoc.name,ddoc.type,blocklist.dns,blocklist.mac from ddoc,blocklist where ddoc.hw_addr=blocklist.mac;'
         let list = await connection.query(query);
          res.status(200).send({list,message: 'ok' });  
     }
      catch (err) {
        res.status(500).send({ message: 'selecting user error' + err });
    }
    finally {
        pool.releaseConnection(connection);
    }
    });
    router.delete('/',async function (req, res) {
        var connection = await pool.getConnection();
       
        let query1='select * from blocklist where mac=? and dns=?'
        let list = await connection.query(query1,[req.body.mac,req.body.dns]);
       
    
         const query = 'delete from blocklist where mac=? and dns=?;'
         let inse= await connection.query(query,[req.body.mac,req.body.dns]);
   
        
    res.status(201).send({   message: "success"  });
        });
        router.post('/lock',async function (req, res) {
            var connection = await pool.getConnection();
            let query1='select ddoc.num,ddoc.name,ddoc.type,blocklist.dns,blocklist.mac,blocklist.ip from ddoc,blocklist where ddoc.hw_addr=blocklist.mac and blocklist.dns=?;'
            let list = await connection.query(query1,req.body.dns);
           console.log(list[0]);
            var num=list[0].num;
            dns=list[0].dns;
            dns = dns.substring(7,dns.length-1);
            console.log('dns??'+dns);
            console.log(dns);
            let query3='delete from url where urlnum=? and ip=?;'
            let delet= await connection.query(query3,[num,dns]); 
            const query = 'delete from blocklist where mac=? and dns=?;'
             let inse= await connection.query(query,[req.body.mac,req.body.dns]);
             let record = {
                request_policy:'push',
                hw_addr: list[0].mac,  
                ip_addr:dnsSync.resolve(dns)
             };
             var data=JSON.stringify(record);  
            console.log(data);
             var a= convert.stringToBytes(data);
             
             child = exec("/home/pi/AP/shell/signal.sh "+a+"", function (error, stdout, stderr) {
                    console.log('stdout:' + stdout );
                    console.log('stderr:' + stderr);
                        if (error !== null) {
                    console.log('exec error:' + error);
                    }
                    });  
            
        res.status(201).send({   message: "success"  });
            });
module.exports = router;
