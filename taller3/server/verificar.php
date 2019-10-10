<?php
    session_start();
    print_r($_POST);
    if($_POST){
        $usuario = $_POST['usr'];
        $password = $_POST['password'];


        $host = "localhost";
        $user = "root";
        $pass = "12345678";
        $dbname = "hospital";
        // if ($_SERVER["REQUEST_METHOD"]=="POST"){
        //     echo "hola";
        // }        
        
            $conn = new mysqli($host, $user, $pass, $dbname);

            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
            } 
            $sql = "SELECT 'OK' as cod FROM cuentas cu WHERE cu.usuario='".$usuario."' AND cu.password='".$password."'";
            $result = $conn->query($sql);
            if ($result->num_rows > 0) {
                if($row = $result->fetch_assoc()) {
                    if($row['cod']=="OK"){
                        echo "Bienvenido ". $usuario;
                        $_SESSION['usuario'] = $usuario;
			            $_SESSION['password'] = $password;
                        print "<script>window.location='../';</script>";
                    }
                }
            }else{
                print "<script>window.location='../?msj=no existes';</script>";   
            }
            $conn->close();
    }else{
        
        // if (!(isset($_SESSION['usuario']) && isset($_SESSION['password']))){
        //     print "<script>window.location='../';</script>";   
        // }
        // else
        // {   
        //     echo "Bienvenido ".$_SESSION['usuario'];
        //     //print "<script>window.location='../';</script>";
        // }
        print "<script>window.location='../';</script>";
    } 
?>