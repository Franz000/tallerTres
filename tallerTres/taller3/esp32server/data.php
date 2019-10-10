<?php
 $host = "localhost";
 $user = "root";
 $pass = "123456789";
 $dbname = "hospital";
 
 $apik = "franz123456789";
 if ($_SERVER["REQUEST_METHOD"]=="POST"){
     $api = $_POST["api"];
     if($api == $apik){
        $conn = new mysqli($host, $user, $pass, $dbname);

        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
         $ecg = $_POST["hr"];
         $spo2 = $_POST["spo2"];
         $id_paciente = $_POST["pa"];
         $sqlp = "INSERT INTO saturacionO2 (codigo_paciente,ecg,SATO2) VALUES (".$id_paciente.",".$ecg.",".$spo2.");";
         $conn ->query($sqlp);
         $conn->close();

     }else{
         echo "ERROR DE KEY <hr>";
     }
 }else{
     echo "ERROR";
 }
?>