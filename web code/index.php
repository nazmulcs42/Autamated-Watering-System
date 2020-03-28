<?php  

	include('db_connect.php');
?>

<!DOCTYPE html> 
<html>
	<head> 
		<title>IoT Smart Watering System</title> 
		<meta name="viewport" content="width=device-width, initial-scale=1.0"> 
		<link href="css/bootstrap.min.css" rel="stylesheet"> 
		<link rel="stylesheet" href="css/index.css">
	</head> 
	<body> 
		

		<div class="container-fluid">
			<div class="row">
				<div class="col-lg-12 col-md-12 col-xs-12 header">
					<h2>IoT Smart Watering System</2>
				</div>
			</div>
			<div class="row">
				<?php

					$sql="SELECT * FROM sensor_value order by id desc limit 5";
					$res=mysqli_query($conn,$sql);


					if (mysqli_num_rows($res)>0) {
						echo "<br>Last updated 5 sensors values <br><br>";
						while ($row=mysqli_fetch_assoc($res)) {
										
							echo "Sensor value: ".$row['value']." At ";
							$timestamp = $row['time'];
							$splitTimeStamp = explode(" ",$timestamp);
							$date = $splitTimeStamp[0];
							//$time = $splitTimeStamp[1];
							$time=date("g:i A", strtotime($row['time']));
							$date=date("d-m-Y", strtotime($date));
							echo $time." On ".$date."<br>";
							/*$date = $row['time']; 
							echo date('h:i:s a m/d/Y', strtotime($date))."<br>";*/

							//echo date("g:i A", strtotime($row['time']))."<br>";
						}
					}
					else{
						echo "Fail";
					}

				?>
			</div>
			<div class="row">
				<?php

					$sql="SELECT * FROM watering_time order by id desc limit 5";
					$res=mysqli_query($conn,$sql);


					if (mysqli_num_rows($res)>0) {
						echo "<br>Last updated 5 Watering time <br><br>";
						while ($row=mysqli_fetch_assoc($res)) {
										
							echo "Watering time: ".$row['duration']." sec At ";
							$timestamp = $row['time'];
							$splitTimeStamp = explode(" ",$timestamp);
							$date = $splitTimeStamp[0];
							//$time = $splitTimeStamp[1];
							$time=date("g:i A", strtotime($row['time']));
							$date=date("d-m-Y", strtotime($date));
							echo $time." On ".$date."<br>";
							/*$date = $row['time']; 
							echo date('h:i:s a m/d/Y', strtotime($date))."<br>";*/

							//echo date("g:i A", strtotime($row['time']))."<br>";
						}
					}
					else{
						echo "Fail";
					}

				?>
			</div>
		</div>

		<script src="js/jquery-3.2.1.min.js"></script> 
	</body> 
</html>