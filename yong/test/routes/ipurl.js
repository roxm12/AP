var exec =require('child_process').exec,
child;
const express = require('express');
const router = express.Router();
const pool = require('../config/db_pool');
var convert = require('convert-string');
var dnsSync = require('dns-sync');
router.post('/:num',async function (req, res) {
    try {
        var connection = await pool.getConnection();
        let query1='select hw_addr from ddoc where num=?;'
        let hw= await connection.query(query1,req.params.num);
       var hw1= JSON.stringify(hw);
       hw = JSON.parse(hw1);
        let record = {
          request_policy: "add_ip",
          hw_addr:hw[0].hw_addr,
          block_policy:0,
          ip_addr:dnsSync.resolve(req.body.ip)
       };
         let query='INSERT INTO url (dnum,ip,information) VALUES (?,?,?);'
         let inse= await connection.query(query,[req.params.num,req.body.ip,req.body.information]);
          res.status(201).send({   message: "ok"  });
      console.log(record);
   var data=JSON.stringify(record);  
   var a= convert.stringToBytes(data);

    child = exec("/home/pi/AP/shell/signal.sh "+a+"", function (error, stdout, stderr) {
           console.log('stdout:' + stdout );
           console.log('stderr:' + stderr);
               if (error !== null) {
           console.log('exec error:' + error);
           }
           });  
        } 
      
      catch (err) {
        res.status(500).send({ message: 'error' + err });
      }
      finally {
        pool.releaseConnection(connection);
      }
    });

 
      router.delete('/:urlnum', async function (req, res) {
        try {
          var connection = await pool.getConnection();
          let query2='select ddoc.num,url.urlnum,url.ip,ddoc.hw_addr,ddoc.adult,ddoc.gambling,ddoc.game,ddoc.learning,ddoc.type,ddoc.name,url.locker from ddoc,url where ddoc.num=url.dnum and url.urlnum=?;'
          let urlselct=await connection.query(query2,req.params.urlnum);
          var urlselct1= JSON.stringify(urlselct);
          urlselct = JSON.parse(urlselct1);
          let record = {
            request_policy: "del_ip",
            hw_addr:urlselct[0].hw_addr,
            block_policy:0,
            ip_addr:dnsSync.resolve(urlselct[0].ip)
         };
         
         let query='delete from url where urlnum=?'
         let deletecate= await connection.query(query,req.params.urlnum);
            res.status(201).send({   message: "ok"  });
        console.log(record);
     var data=JSON.stringify(record);  
     var a= convert.stringToBytes(data);
 
      child = exec("/home/pi/AP/shell/signal.sh "+a+"", function (error, stdout, stderr) {
             console.log('stdout:' + stdout );
             console.log('stderr:' + stderr);
                 if (error !== null) {
             console.log('exec error:' + error);
             }
             });  
          } 
        
        catch (err) {
          res.status(500).send({ message: 'delete error' + err });
        }
        finally {
          pool.releaseConnection(connection);
        }
      });
      router.put('/lock/:urlnum', async function (req, res) {
        try {
          var connection = await pool.getConnection();
          let query1='select ddoc.num,url.urlnum,url.ip, ddoc.hw_addr,ddoc.adult,ddoc.gambling,ddoc.game,ddoc.learning,ddoc.type,ddoc.name,url.locker from ddoc,url where ddoc.num=url.dnum and url.urlnum=?;'
          let urlselct=await connection.query(query1,req.params.urlnum);
          var urlselct1= JSON.stringify(urlselct);
          urlselct = JSON.parse(urlselct1);
           let query='UPDATE url SET locker=1 WHERE urlnum=?;'
         let deletecate= await connection.query(query,req.params.urlnum);
            res.status(201).send({   message: "ok"  });
            let record = {
                request_policy:'block_ip',
                hw_addr:urlselct[0].hw_addr,
                blocking_policy: '0',
                ip_addr: dnsSync.resolve(urlselct[0].ip)
              
             };
            console.log(record);
     var data=JSON.stringify(record);  
     var a= convert.stringToBytes(data);
 
      child = exec("/home/pi/AP/shell/signal.sh "+a+"", function (error, stdout, stderr) {
             console.log('stdout:' + stdout );
             console.log('stderr:' + stderr);
                 if (error !== null) {
             console.log('exec error:' + error);
             }
             });  
          } 
        
        catch (err) {
          res.status(500).send({ message: 'delete error' + err });
        }
        finally {
          pool.releaseConnection(connection);
        }
      });
      router.put('/unlock/:urlnum', async function (req, res) {
        try {
          var connection = await pool.getConnection();
          let query1='select ddoc.num,url.urlnum,url.ip, ddoc.hw_addr,ddoc.adult,ddoc.gambling,ddoc.game,ddoc.learning,ddoc.type,ddoc.name,url.locker from ddoc,url where ddoc.num=url.dnum and url.urlnum=?;'
          let urlselct=await connection.query(query1,req.params.urlnum);
          var urlselct1= JSON.stringify(urlselct);
          urlselct = JSON.parse(urlselct1);
           let query='UPDATE url SET locker=0 WHERE urlnum=?;'
         let deletecate= await connection.query(query,req.params.urlnum);
            res.status(201).send({   message: "ok"  });
            let record = {
                request_policy:'unblock_ip',
                hw_addr:urlselct[0].hw_addr,
                blocking_policy: '0',
                 ip_addr: dnsSync.resolve(urlselct[0].ip)
               
             };
            console.log(record);
     var data=JSON.stringify(record);  
     var a= convert.stringToBytes(data);
 
      child = exec("/home/pi/AP/shell/signal.sh "+a+"", function (error, stdout, stderr) {
             console.log('stdout:' + stdout );
             console.log('stderr:' + stderr);
                 if (error !== null) {
             console.log('exec error:' + error);
             }
             });  
          } 
        
        catch (err) {
          res.status(500).send({ message: 'delete error' + err });
        }
        finally {
          pool.releaseConnection(connection);
        }
      });
      router.put('/blist/:num', async function (req, res) {
        try {
          var connection = await pool.getConnection();
          let query1='select hw_addr,adult,gambling,game,learning from ddoc where num=?;'
          let hw= await connection.query(query1,req.params.num);
         var hw1= JSON.stringify(hw);
         hw = JSON.parse(hw1)
           let query='UPDATE ddoc SET adult=?,gambling=?,game=?,learning=? WHERE num=?;'
         let deletecate= await connection.query(query,[req.body.adult,req.body.gambling,req.body.game,req.body.learning,req.params.num]);
         var bin1 =[hw[0].adult,hw[0].gambling,hw[0].game,hw[0].learning];
         var bin = [req.body.adult,req.body.gambling,req.body.game,req.body.learning];
         bin=req.body.adult*8+req.body.gambling*4+req.body.game*2+req.body.learning*1;   
         bin1=hw[0].adult*8+hw[0].gambling*4+hw[0].game*2+hw[0].learning*1;   
         res.status(201).send({   message: "ok"  });
            let record = {
                request_policy:'upd_Blist',
                hw_addr:hw[0].hw_addr,
              pre_block_policy:bin1,
                block_policy: bin,
                ip_addr:null  
             };
            console.log(record);
     var data=JSON.stringify(record);  
     var a= convert.stringToBytes(data);
 
      child = exec("/home/pi/AP/shell/signal.sh "+a+"", function (error, stdout, stderr) {
             console.log('stdout:' + stdout );
             console.log('stderr:' + stderr);
                 if (error !== null) {
             console.log('exec error:' + error);
             }
             });  
          } 
        
        catch (err) {
          res.status(500).send({ message: 'delete error' + err });
        }
        finally {
          pool.releaseConnection(connection);
        }
      });
module.exports = router;


   // router.get('/:num', (req, res) => {
    //     return new Promise((fulfill, reject) => {
    //       pool.getConnection((err, connection) => {
    //         if(err) reject(err);
    //         else fulfill(connection);
    //       });
    //     })
    //     .catch(err => { res.status(500).send({ result: [], message: 'getConnection error : '+err}); })
    //     .then(connection => {
    //       return new Promise((fulfill, reject) => {
    //         let query = 'SELECT ip,locker FROM url where dnum=?;' 
    //           connection.query(query,req.params.num, (err, data) => {
    //             if(err) res.status(500).send({ result: [], message: 'selecting error: '+err });
    //             else res.status(200).send({ result : data, message: 'ok' });
    //             connection.release();
    //           });
    //       });
    //     })
    //   });
