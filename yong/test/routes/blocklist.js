var exec =require('child_process').exec,
child;
const express = require('express');
const router = express.Router();
const pool = require('../config/db_pool');
var convert = require('convert-string');
router.post('/',async function (req, res) {
    var connection = await pool.getConnection();
    let record = {
        request_policy:'reg_host',
        hw_addr: req.body.hw_addr,
        blocking_policy: '0',
        user_defined:null  
     };
     const query = 'INSERT INTO ddoc (hw_addr,type,name) VALUES (?,?,?);'
     let inse= await connection.query(query,[req.body.hw_addr,req.body.type,req.body.name]);
     
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
    router.get('/', (req, res) => {
        return new Promise((fulfill, reject) => {
          pool.getConnection((err, connection) => {
            if(err) reject(err);
            else fulfill(connection);
          });
        })
        .catch(err => { res.status(500).send({ result: [], message: 'getConnection error : '+err}); })
        .then(connection => {
          return new Promise((fulfill, reject) => {
            let query = 'SELECT num,name,hw_addr,type FROM ddoc;' 
              connection.query(query, (err, data) => {
                if(err) res.status(500).send({ result: [], message: 'selecting error: '+err });
                else res.status(200).send({ result : data, message: 'ok' });
                connection.release();
              });
          });
        })
      });
      router.delete('/:num', async function (req, res) {
        try {
          var connection = await pool.getConnection();
          let query1='select hw_addr from ddoc where num=?;'
          let hw= await connection.query(query1,req.params.num);
         var hw1= JSON.stringify(hw);
         hw = JSON.parse(hw1)
          let record = {
            request_policy: "del_host",
            hw_addr:hw[0].hw_addr,
            block_policy:0,
            user_defined:null
         };
           let query='delete from ddoc where num=?'
         let deletecate= await connection.query(query,req.params.num);
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
      router.put('/:num', async function (req, res) {
        try {
          var connection = await pool.getConnection();
           let query='UPDATE ddoc SET hw_addr=?,type=?,name=? WHERE num=?;'
         let deletecate= await connection.query(query,[req.body.hw_addr,req.body.type,req.body.name,req.params.num]);
            res.status(201).send({   message: "ok"  });
            let record = {
                request_policy:'upd_host',
                hw_addr: req.body.hw_addr,
                blocking_policy: '0',
                user_defined:null  
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
          res.status(500).send({ message: 'update error' + err });
        }
        finally {
          pool.releaseConnection(connection);
        }
      });
      
module.exports = router;
