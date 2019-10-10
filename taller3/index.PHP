<?php
    session_start();
    $seson_activa = false;
    echo "<script>alert(".$_SESSION['usuario']." ".$_SESSION['password'].")</script>"; 
    if (isset($_SESSION['usuario']) && isset($_SESSION['password'])){
        $seson_activa=true;
    }

?>
<!DOCTYPE html>
<html lang="en" class="h-100">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Proyecto</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width = device-width, initial-scala=1, shrink-to-fit = no">
    <meta http-equiv="x-ua-compatible" content="ie-edge">
    <link rel="stylesheet" type="text/css" href="css/bootstrap.css">

    <script src="script/jquery-3.4.0.min.js"></script>
    <script src="script/jquery.min.js"></script> 
    <?php if($seson_activa){ ?>
    <script src="script/mostrar_data.js"></script> 
    <?php } ?>
</head>

<body class="text-center h-100">


<?php
        if($seson_activa==false){
    ?>
    <div class="page-header">
        <h1>TELEMONITOREO DE PACIENTES EN UNA RED LOCAL</h1>
    </div>
    <div class="container w-25" style="padding-top: 10%">    
        <form method="POST" action="server/verificar.php" class=" mr-auto ml-auto mt-auto mb-auto">
        <img class="mb-4" src="img/agrehar usuario.png" alt="" width="72" height="72">
        <h1 class="h3 mb-3 font-weight-normal">Logueate</h1>
        <?php
        if($_GET)
        {
            $msj = $_GET['msj'];
            ?>
            <span style="color: red;"><?php echo $msj; ?></span>
            <?php
        }
        ?>
        <label for="usr" class="sr-only">Usuario</label>
        <input type="text" id="usr" name="usr" class="form-control" placeholder="Usuario" required="" autofocus="">
        <label for="password" class="sr-only">Password</label>
        <input type="password" id="password" name="password" class="form-control" placeholder="Password" required="">
        <div class="checkbox mb-3">
            <label>
                <input type="checkbox" value="remember-me"> Recuerdame
            </label>
        </div>
        <input class="btn btn-lg btn-info btn-block" type="submit" value="Sign in">
        <button type="button" name="" id="" class="btn btn-danger btn-block"
        onclick="window.location.href='registrar.html'" >
            Registrar
        </button>
        <span class="mt-5 mb-3 text-muted">Taller 3 ©2019</span>
    </form>

</div>


<?php
        }else{
    ?>
    <script>
        
    </script>
    <h1><?php echo "Bienvenido Dr.".$_SESSION['usuario'];?></h1>
    <form method="POST" action="server/desconectar.php">
        <input type="submit" value="Desconectar" name="desconectar">
    </form>

    <div class="contenedor" id="contenedor"></div>
    
    <?php
        }
    ?>

    <!-- <script src="js/jquery-3.3.1.slim.min.js"></script>
    <script src="js/popper.min.js"></script>
    <script src="js/bootstrap.min.js"></script> -->
</body>

</html>