<?php  

	include('db_connect.php');
	$temp=$_POST['watering_time'];

	$sql = "INSERT into watering_time(duration) values('$temp')";
	$res = mysqli_query($conn,$sql);
	if ($res) {
		echo "success";
	}
	else{
		echo "fail";
	}
	
	
?>