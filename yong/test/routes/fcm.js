var exec =require('child_process').exec,
child;
const express = require('express');
const router = express.Router();
const arp =require('node-arp');
const pool = require('../config/db_pool');
const FCM = require('fcm-push');
const requestIp=require('request-ip');
const serverKey = require('../config/serverKey').serverKey;
var fcm = new FCM(serverKey);

    router.post('/', async(req, res)=>{
        try{
            var connection = await pool.getConnection();
            let query = 'select deviceToken from admin';
            let writer = await connection.query(query);
            var dns=req.body.dns;
            console.log(dns);
       
            mac=requestIp.getClientIp(req);
         mac=JSON.stringify(mac);
         mac = mac.substring(8,mac.length-1);
         console.log(mac);
       arp.getMAC(mac,function(err,mac){
               if(!err){
               console.log(mac);
               }
               });
         //알람부르기 & 메세지전송 & 저장
              var message = {
                  to: writer[0].deviceToken , // required fill with device token or topics
                  notification: {
                      title: '요청',
                      body: '차단요청이 왔습니다.'
                  }
              };
              let query2 = 'insert into blocklist set ?';
              let record2 = {
                "mac" : mac,
                "dns" : req.body.dns
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
       
          let query='select * from blocklist;'
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
module.exports = router;
