<?php
 $host = "localhost";
 $user = "root";
 $pass = "123456789";
 $dbname = "hospital";
 
 
    $conn = new mysqli($host, $user, $pass, $dbname);

    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    } 
    $ecg = $_POST["hr"];
    $spo2 = $_POST["spo2"];
    $id_paciente = $_POST["pa"];
    $sqlp = "SELECT * FROM saturacionO2;";
    $result = $conn->query($sql2);
    if ($result->num_rows > 0) {
        while($row = $result->fetch_assoc()) {
            echo "id:           ".$row['id']."<br>";
            echo "cod_paciente: ".$row['codigo_paciente']."<br>";
            echo "ECG:          ".$row['ecg']."<br>";
            echo "SATO2:        ".$row['SATO2']."<br>";
            echo "FECHA:        ".$row['fecha']."<hr>";
        }
    }
    
    $conn->close();
?>