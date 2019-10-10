<?php
    session_start();
    $seson_activa = false;
    if (isset($_SESSION['usuario']) && isset($_SESSION['password'])){
        $seson_activa=true;
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Proyecto III</title>
    <script src="script/jquery-3.4.0.min.js"></script>
    <script src="script/jquery.min.js"></script> 
    <script src="script/mostrar_data.js"></script>   
</head>
<body>
    <?php
        if($seson_activa==false){
            if($_GET)
            {
                $msj = $_GET['msj'];
                ?>
                <p style="color: red;"><?php echo $msj; ?></p>
                <?php
            }
    ?>
    <form method="POST" action="server/verificar.php">
        <label for="usuario">Usuario:</label>
        <input type="text" id="usuario" name="usr" placeholder="usuaario"><br>
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" placeholder="password"><br>
        <input type="submit" value="Ingresar">
    </form>
    <?php
        }else{
    ?>
    <h1><?php echo "Bienvenido Dr.".$_SESSION['usuario'];?></h1>
    <form method="POST" action="server/desconectar.php">
        <input type="submit" value="Desconectar" name="desconectar">
    </form>

    <div class="contenedor" id="contenedor"></div>
    
    <?php
        }
    ?>
</body>
</html>