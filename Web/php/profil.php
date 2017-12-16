<?php
include("header.php");
include("sesija.php");
include("navigacija_admin.php");
include("baza.php");
$korisnik = $_SESSION['korisnik'];

$profil = "SELECT * FROM user WHERE email ='".$korisnik."'";
	$rezultat=$baza->query($profil);
	
  if ($rezultat) {
	
   while($redak=$rezultat->fetch_assoc()){
		$lal = $redak['email'];
        	echo'
		<div class="container">
		<div class="row">';
if(isset($_GET['Message'])){
    
	echo $_GET['Message'];
}
         echo'   <div class="col-md-3" >
			<div id="slike">
				<img width="200" height="200" id="odabranaSlika" src="slike/'.$redak['slika'].'"/>
				
			 </div>
				
            </div>
			<div class="col-md-4">
			<h3>Email: '.$redak['email'].'</h3>
			<h3>Username: '.$redak['username'].'</h3>
			
			<a class="btn btn-primary btn-lg" href="editProfil.php">Change password</a>
			<a class="btn btn-primary btn-lg" href="avatar.php">Change avatar</a>
			</div>
        </div>
		</div>
		';    
			}
}


include("footer.php");
?>