<?php
session_start();
    if($_POST){
        $usuario = $_POST['usr'];
        $password = $_POST['password1'];
        $password2 = $_POST['password2'];
        if($password == $password2){
            $host = "localhost";
            $user = "root";
            $pass = "12345678";
            $dbname = "hospital";    
            $conn = new mysqli($host, $user, $pass, $dbname);
            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
            }
            $sql = "INSERT INTO cuentas (usuario,password) VALUES('$usuario','$password')";
            $conn->query($sql);
            $_SESSION['usuario'] = $usuario;
            $_SESSION['password'] = $password;
            $conn->close();
        }
    }
    print "<script>window.location='../';</script>";
?>