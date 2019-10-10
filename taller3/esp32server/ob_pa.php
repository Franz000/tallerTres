<?php
    $host = "localhost";
    $user = "root";
    $pass = "123456789";
    $dbname = "hospital";
    $apikey = "franz123456789";
    if($_GET)
    {
        if($_GET['api']==$apikey){
            $conn = new mysqli($host, $user, $pass, $dbname);

            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
            }

            $sql = "SELECT * FROM equipo_monitoreo WHERE apikey = '".$apikey."';";

            $result = $conn->query($sql);

            if ($result->num_rows > 0) {
                if($row = $result->fetch_assoc()) {
                    $id_equipo = $row['id'];
                }
            }
            if(isset($id_equipo)){
                $sql2 = "SELECT *
                FROM equipo_paciente
                WHERE id_equipo=".$id_equipo."
                ORDER by fecha DESC
                LIMIT 1";
                $result = $conn->query($sql2);
                if ($result->num_rows > 0) {
                    if($row = $result->fetch_assoc()) {
                        $id_paciente = $row['id_paciente'];
                    }
                }
                if(isset($id_paciente)){
                    echo $id_paciente;
                }
                else{
                    echo "no hay paciente";
                }
            }else{
                echo "no hay equipo";
            }
            $conn->close();
        }
    }    
?>