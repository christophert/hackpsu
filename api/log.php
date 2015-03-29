<?php
require("../../../db.php");
	$stmt = $conn->prepare("select * from events");
	if($stmt->execute()) {
		while($r = $stmt->fetch(PDO::FETCH_ASSOC)) {
			$response[] = array('event' => $r);
		}
	}

session_start();
header("Content-Type: application/json");
$end['log'] = $response;
echo json_encode($end);
?>