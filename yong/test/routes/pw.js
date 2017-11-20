var exec =require('child_process').exec,
	child;
const express = require('express');
const router = express.Router();

router.post('/',function (req, res) {
		
		const pw = req.body.pw;
		console.log(pw);
		child = exec("/home/pi/garim/pw.sh " +pw+"", function (error, stdout, stderr) {
				console.log('stdout:' + stdout);
				console.log('stderr:' + stderr);
				if (error !== null) {
				console.log('exec error:' + error);
				}
				});  
		
res.status(201).send({   message: "success"  });


		});

module.exports = router;




