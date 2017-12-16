<?php
        $baza=new mysqli('localhost','root','','test');
		if ($baza->connect_error) {
				echo '<div class="alert alert-danger">
                <strong>Nije se moguće spojiti na bazu podataka</strong> </div>';
                exit();
		}
        $baza->set_charset('utf8');
?>