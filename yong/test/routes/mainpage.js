var exec =require('child_process').exec,
child;
const express = require('express');
const router = express.Router();
const pool = require('../config/db_pool');
var convert = require('convert-string');
var network=require('network');
  router.get('/', async function (req, res) {
    try {
      var connection = await pool.getConnection();
   
      let info='select ddoc.num,ddoc.hw_addr,ddoc.adult,ddoc.gambling,ddoc.game,ddoc.learning,ddoc.type,ddoc.name from ddoc order by num;'
     let all=await connection.query(info);
     var query='';
     var information=[];
     var result=[];
   for(var i in all)
{
   query = 'select dnum,urlnum,ip,locker from url where dnum=?;'
   information[i] = await connection.query(query,all[i].num);
  
}
var all1= JSON.stringify(all);
all = JSON.parse(all1);
var information1= JSON.stringify(information);
information = JSON.parse(information1);
for(var i in all)
  {
      if(all[i].num)
        {
       result[i]={
         num:all[i].num,
         hw_addr:all[i].hw_addr,
         adult:all[i].adult,
         gambling:all[i].gambling,
         game:all[i].game,
         learning:all[i].learning,
         type:all[i].type,
         name:all[i].name,
        information:information[i]
      };
        }
   
      }
    //  let query = 'select urlnum,ip,locker from url;' 
    //  let information=await connection.query(query);
      res.status(200).send({result,message: 'ok' }); 
 }
  catch (err) {
    res.status(500).send({ message: 'selecting user error' + err });
}
finally {
    pool.releaseConnection(connection);
}
});
router.get('/al', async function (req, res) {
  try {
    var connection = await pool.getConnection();
   network.get_active_interface(function(err,obj){
           console.log(obj);
           });
           
 
  
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
