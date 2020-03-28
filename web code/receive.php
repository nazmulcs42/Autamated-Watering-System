<?php  

	include('db_connect.php');
	$temp=$_POST['sensor_value'];

	$sql = "INSERT into sensor_value(value) values('$temp')";
	$res = mysqli_query($conn,$sql);
	if ($res) {
		echo "success";
	}
	else{
		echo "fail";
	}
	
	
?>