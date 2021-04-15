<html>
<?php
$valor = $_GET['voz'];
if($valor=='enciende patio' ) { system ("sudo python3 patioon.py");
}
if ($valor=='enciende toma' ) { exec("sudo python3 /var/www/html/tomaon.py");
}
if ($valor=='enciende parqueo' ) { exec("sudo python3 /var/www/html/garajeon.py");
}
if ($valor=='enciende sala' ) { exec("sudo python3 /var/www/html/salaon.py");system("sudo python3 /var/www/html/ejemplo2_on.py ");
}
if ($valor=='abrir puerta' ) { exec("sudo python3 /var/www/html/puertaon.py");
}
if ($valor=='enciende todo' ) { exec("sudo python3 /var/www/html/todoon.py");
}
if ($valor=='foto') { exec("sudo python3 /var/www/html/foto.py");
}
if($valor=='apaga patio' ) { exec("sudo python3 /var/www/html/patiooff.py");
}
if($valor=='apaga toma' ) { exec("sudo python3 /var/www/html/tomaoff.py");
}
if($valor=='apaga parqueo' ) { exec("sudo python3 /var/www/html/garajeoff.py");
}
if($valor=='apaga sala' ) { exec("sudo python3 /var/www/html/salaoff.py");system("sudo python3 /var/www/html/ejemplo2_off.py ");
}
if ($valor=='cerrar puerta' ) { exec("sudo python3 /var/www/html/puertaoff.py");
}
if ($valor=='apaga todo' ) { exec("sudo python3 /var/www/html/todooff.py");
}
 echo "<script> window.close();</script>"
?>
</html>
