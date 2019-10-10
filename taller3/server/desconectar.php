<?php
    session_start();
    if($_POST){
        if($_POST['desconectar']=="Desconectar"){
            if (isset($_SESSION['usuario']) && isset($_SESSION['password'])){
                unset($_SESSION['usuario']);
                unset($_SESSION['password']);
                session_destroy();
            }
        }
    }
    print "<script>window.location='../';</script>";  
?>
