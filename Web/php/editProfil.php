<?php
include("header.php");
include("navigacija_admin.php");
include("sesija.php");
include("baza.php");
include('../PFBC/Form.php');
$korisnik = $_SESSION['korisnik'];
Form::clearValues("izmjeniKorisnik");

echo '<div class="edit"><h2>Change password</h2>';
if (isset($_POST['predano'])) {
		$id=$_POST['id'];
		
		$loz =$_POST['loz'];
		
	
	if(Form::isValid("izmjeniKorisnik", false)) {
		
		if($_POST["lozinka1"]== $_POST["lozinka2"]) {
					
					
					$stara = htmlentities(trim($_POST['Staralozinka']));

					if($stara==$loz ){
						$lozinka=htmlentities(trim($_POST['lozinka1']));
					$izjava=$baza->prepare('UPDATE user SET  password=? WHERE id=?');
					$izjava->bind_param('sd', $lozinka, $id);
					if ($izjava->execute()) {
						
						$Message = urlencode('<div class="alert alert-success">
									 <strong>Password changed!!</strong>
										</div>');			
										
					}else {
						Form::setError("izmjeniKorisnik", "Error");
								}
					}else{
						echo '<div class="alert alert-danger">
									 <strong>Old password is wrong!</strong>
										</div>';
					 $Message = urlencode('<div class="alert alert-danger">
									 <strong>Old password is wrong!</strong>
										</div>');
					}
					
				} else {
					Form::setError("izmjeniKorisnik", "Passwords do not match!");
				}
				$baza->close();
				
				
				header('Location: profil.php?Message='.$Message);
		}			
		
	}else{
		$profil = "SELECT * FROM user WHERE email ='".$korisnik."'";
	$rezultat=$baza->query($profil);
	
		if ($rezultat) {
	
			while($redak=$rezultat->fetch_assoc()){
			$id = $redak['id'];
			$email = $redak['email'];
			$loz = $redak['password'];
          
			}
		}
	}



Form::open ('izmjeniKorisnik');
	Form::Hidden ('predano', 'da');
	Form::Hidden ('id', $id);
	Form::Hidden('loz',$loz);

	 Form::Password("Old password:", "Staralozinka");
	 Form::Password("New password:", "lozinka1");
	 Form::Password("Confirm new password:", "lozinka2");
	 echo'<div class="gumbovi">';
	Form::Button('Change');
	Form::Button('Cancel', 'button', array("onclick" => "location.href='profil.php';"));
	echo '</div>';
	Form::close (false);
	echo'</div>';
include("footer.php");
?>