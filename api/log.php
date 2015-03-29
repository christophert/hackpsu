<?php
require("../../../db.php");
	$stmt = $conn->prepare("select * from events");
	if($stmt->execute()) {
		$response = $stmt->fetch(PDO::FETCH_ASSOC);
	}

session_start();
$response = getAllEntries();
header("Content-Type: application/json");
$end['log'] = $reponse;
echo json_encode($end);
?>