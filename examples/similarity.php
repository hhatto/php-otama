<?php

$otama = new Otama();

$otama->open("./nodb.conf");

$filename1 = "images/lena.jpg";
$filename2 = "images/lena-affine.jpg";
var_dump($otama->similarity($filename1, $filename2));
