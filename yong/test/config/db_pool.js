const mysql = require('promise-mysql');
const dbConfig = {
  host: '172.24.1.1',
  port: 3306,
  user: 'root',
  password: 'raspberry',
  database: 'ddoc',
  connectionLimit: 23
};
// const dbConfig = {
//   host: 'localhost',
//   port: 3306,
//   user: 'root',
//   password: '1234',
//   database: 'pokemon',
//   connectionLimit: 23
// };
const db_pool = mysql.createPool(dbConfig);
module.exports = db_pool;
