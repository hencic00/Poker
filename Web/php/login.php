<?php

	
	include ('header.php');
	include('navigacija_admin.php');
	include('sesija.php');
	echo '<div class="forma"><h2>Login</h2>';
	 include('../PFBC/Form.php');
	if (isset($_POST['predano'])) {
	if(Form::isValid("login", false)) {
					require_once('baza.php');
					$korisnik=htmlentities(trim($_POST['korisnik']));
					$lozinka=htmlentities(trim($_POST['lozinka']));
					$izjava=$baza->prepare('SELECT * FROM user WHERE email=? LIMIT 1');
					$izjava->bind_param('s', $korisnik);
					if ($izjava->execute()) {
						$rezultat=$izjava->get_result();
						$redak=$rezultat->fetch_assoc();
						if (count($redak)) {
							if ($redak['password']==$lozinka) {
								//redirekcija
								$_SESSION['korisnik']=$korisnik;
								header('Location: ../index.php');
								echo '<script>alert($korisnik);</script>';
							} else {
								Form::setError("login", "Wrong password");
							}
						} else{
							Form::setError("login", "User does not exist!");
						}
						
					} else {
						Form::setError("login", "Something went wrong.");
					}		
					$baza->close();
		}
	}

	
	
	Form::open ('login');
	Form::Hidden ('predano', 'da');
	Form::Textbox ("Username", "korisnik", array(
		"required" => 1));
	 Form::Password("Password", "lozinka", array(
		"required" => 1));
	Form::Button('Login');
	Form::close (false);
	echo "</div>";
	echo'<div>';
	echo '</div>';
	include('footer.php');
?>

