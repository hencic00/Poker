<?php


	include ('header.php');
	include("sesija.php");
	include ('navigacija_admin.php');
	echo '<div class="forma"><h2>Upload avatar</h2>';
	include('../PFBC/Form.php');
	
	if (isset($_POST['predano'])) {
	if(Form::isValid("avatarForm", false)) {
				Form::clearValues("avatarForm");
					require_once('baza.php');
					$korisnik = $_SESSION['korisnik'];
							require_once('crop.php');
						  $dozvoljeni_MIME=array("image/jpeg", "image/gif", "image/png", "image/bmp");  
						  if(!empty($_FILES['slika']['type'])&&!in_array($_FILES['slika']['type'], $dozvoljeni_MIME)) {
							Form::setError("avatarForm", "Wrong format! (gif, jpeg ili png)");
						  } else {
							$greska = $_FILES['slika']['error']; 
							$upload_greske = array(
							  UPLOAD_ERR_OK=> "Image uploaded !",
							  UPLOAD_ERR_INI_SIZE  => "File too large",
							  UPLOAD_ERR_FORM_SIZE => "File too large",
							  UPLOAD_ERR_PARTIAL => "Partial upload.",
							  UPLOAD_ERR_NO_FILE => "No file was selected",
							  UPLOAD_ERR_NO_TMP_DIR => "Server error",
							  UPLOAD_ERR_CANT_WRITE => "Server error",
							  UPLOAD_ERR_EXTENSION=> "Extension error"
							);
							if ($greska>0) {
							 Form::setError("avatarForm", $upload_greske[$greska]);	  
							} else {
								  $privremena_datoteka=$_FILES['slika']['tmp_name'];
								  $datoteka_spremanja=basename($_FILES['slika']['name']);
								  $posljednjaTocka = strrpos($datoteka_spremanja, ".");
								  $ekstenzija= substr($datoteka_spremanja, $posljednjaTocka);
								  $datoteka_spremanja= str_replace(".", "", substr($datoteka_spremanja, 0, $posljednjaTocka));
								  $datoteka_spremanja= str_replace(" ", "", $datoteka_spremanja);
								  if (strlen($datoteka_spremanja)>50) $datoteka_spremanja= substr($datoteka_spremanja, 0, 50);
								  $datoteka_spremanja.=$ekstenzija;
								  $upload_dir="slike";
									$i=0;
									while (file_exists($upload_dir."/".$datoteka_spremanja)) {	 
									  list ($naziv, $ekstenzija)=explode(".", $datoteka_spremanja);
									  $datoteka_spremanja=rtrim($naziv, strval($i-1)) . $i . "." . $ekstenzija;
									  $i++;
								}
								$slika=$upload_dir. "/" . $datoteka_spremanja;
									if (move_uploaded_file($privremena_datoteka, $slika)) {
											if (true !== ($greska_sa_slikom= image_resize($slika, $slika, 200, 200, 1))) {
											 unlink($slika);
											} else {
												$izjava=$baza->prepare('UPDATE user SET slika=? WHERE email=?');
												  $izjava->bind_param('ss', $datoteka_spremanja, $korisnik);
												  
												  if ($izjava->execute()) {
														header('Location: profil.php');
													echo '<div class="alert alert-success"><strong>Image uploaded!</strong></div>';
												} else {
													Form::setError("avatarForm", "Server error!");
												}
											}
									} else {
									 Form::setError("avatarForm", "Server error!");
								  }
								}	
							}
						
					$baza->close();
		}	
	}


	
	
	Form::open ('avatarForm', '', array("enctype"=>"multipart/form-data"));
	Form::Hidden ('predano', 'da');
	Form::File("Avatar", "slika", array ("required" => 1));

	Form::Button('Upload');
	Form::close (false);
	echo "</div>";
	include('footer.php');
?>

