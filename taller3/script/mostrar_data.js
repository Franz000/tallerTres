setInterval(() => {
    $.ajax({
        type: 'POST',
        url: "server/data_all.php",
        // data: $('form').serialize(),
        cache: false,
        success: function (html) {
            $("#contenedor").html(html);
            console.log(html);
            // setTimeout(function () {
            //     $("#contenedor").html("");
            // }, 8000);
        }
    });
}, 1000);

// clearInterval(hola);