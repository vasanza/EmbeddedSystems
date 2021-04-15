<iframe width="560" height="315" src="https://www.youtube.com/embed/Va6Bt5VrlrA" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>


<html>
<head>
<meta name="viewport" content="width=device-width" />
<title>PRÁCTICA 12 SISTEMAS EMBEBIDOS.</title>
</head>
       <body>
       <center><h1>Control web SISTEMAS EMBEBIDOS 2020 IIT</h1>
         <form method="get" action="botones.php">
            <input type="submit" style = "font-size: 16 pt" value="ApagarPatio" name="offPatio">
            <input type="submit" style = "font-size: 16 pt" value="EncenderPatio" name="onPatio">
         </form></center>

	<center><form method="get" action="botones.php">
         <input type="submit" style = "font-size: 16 pt" value="ApagarParqueo" name="offParqueo">
            <input type="submit" style = "font-size: 16 pt" value="EncenderParqueo" name="onParqueo">
         </form></center>

	<center><form method="get" action="botones.php">
         <input type="submit" style = "font-size: 16 pt" value="ApagarSala" name="offSala">
            <input type="submit" style = "font-size: 16 pt" value="EncenderSala" name="onSala">
         </form></center>

	<center><form method="get" action="botones.php">
         <input type="submit" style = "font-size: 16 pt" value="ApagarEntrada" name="offEntrada">
            <input type="submit" style = "font-size: 16 pt" value="EncenderEntrada" name="onEntrada">
         </form></center>

<?php
     if(isset($_GET['offPatio']))
        {
                       echo "Patio apagado";
                        system ("sudo python3 patiooff.py");
        }
            else if(isset($_GET['onPatio']))
            {
                        echo "Patio encendido";
                        exec("sudo python3 patioon.py");
            }
            else if(isset($_GET['onParqueo']))
            {
                        echo "Parqueo encendido";
                        exec("sudo python3 garajeon.py");
            }
            else if(isset($_GET['offParqueo']))
            {
                        echo "Parqueo apagado";
                        exec("sudo python3 garajeoff.py");
            }
            else if(isset($_GET['onSala']))
            {
                        echo "Sala encendida";
                        exec("sudo python3 salaon.py");
			system("sudo python3 ejemplo2_on.py");
            }
            else if(isset($_GET['offSala']))
            {
                        echo "Sala Apagada";
                        exec("sudo python3 salaoff.py");
			system("sudo python3 ejemplo2_off.py");
            }
            else if(isset($_GET['onEntrada']))
            {
                        echo "Entrada encendida";
                        exec("sudo python3 entradaon.py");
            }
            else if(isset($_GET['offEntrada']))
            {
                        echo "Entrada apagada";
                        exec("sudo python3 entradaoff.py");
            }
	else{
			echo "SELECCIONE ACCIÓN";
	    }
?>
   </body>
</html>	
