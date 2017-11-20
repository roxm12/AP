var exec =require('child_process').exec,
	child;
const express = require('express');
const router = express.Router();

router.post('/',function (req, res) {
		
		const name = req.body.name;
		console.log(name);
		child = exec("/home/pi/garim/preferences/name.sh " +name+"", function (error, stdout, stderr) {
				console.log('stdout:' + stdout);
				console.log('stderr:' + stderr);
				if (error !== null) {
				console.log('exec error:' + error);
				}
				});  
		
res.status(201).send({   message: "success"  });


		});

module.exports = router;




