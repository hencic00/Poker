<?php


	include ('header.php');
	include ('navigacija_admin.php');
	echo "<script>
		document.getElementById('korisnici').classList.add('active');
		document.getElementById('noviKor').classList.add('active');
	</script>";
	echo '<div class="forma"><h2>Kreiraj novog korisnika</h2>';
	include('../PFBC/Form.php');
	
	if (isset($_POST['predano'])) {
	if(Form::isValid("noviKorisnik", false)) {
			if($_POST["lozinka"]== $_POST["lozinka2"]) {
				Form::clearValues("noviKorisnik");
				//upis korisnika u bazu podataka
					require_once('baza.php');
					//provjera da li se nalazi u bazi
					$korisnik=htmlentities(trim($_POST['korisnik']));
					$lozinka=sha1(htmlentities(trim($_POST['lozinka'])));
					$email = htmlentities(trim($_POST['email']));
					$izjava=$baza->prepare('SELECT * FROM korisnici WHERE korisnik=? LIMIT 1');
					$izjava->bind_param('s', $korisnik);
					if ($izjava->execute()) {
						$rezultat=$izjava->get_result();
						if (count($rezultat->fetch_assoc())) {
							Form::setError("noviKorisnik", "Korisnik je već upisan u bazu. Koristite drugo korisničko ime");
						} else{
							//provjera za slike
							require_once('crop.php');
						 //potrebno je odrediti koji su dozvoljeni tipovi podataka, u našem primjeru korisniku dozvoljavamo samo slikovne datoteke pa smo zadali te MIME tipove podataka
						  $dozvoljeni_MIME=array("image/jpeg", "image/gif", "image/png", "image/bmp");
						  
						  //provjeravamo da tip podataka nije prazan- da je korisnik nešto predao, a
						  //s in_array funkcijom provjeravamo da li tip datoteke odgovara zadanim mime tipovima  
						  if(!empty($_FILES['slika']['type'])&&!in_array($_FILES['slika']['type'], $dozvoljeni_MIME)) {
							Form::setError("noviKorisnik", "Niste odabrali ispravan tip datoteke!!! (gif, jpeg ili png)");
						  } else {
							//ako je korisnik predao ispravnu datoteku, s ispravnim tipom podataka
							//provjeravamo da li je nastala neka pogreška prilikom samog upload-a
							$greska = $_FILES['slika']['error']; 
							$upload_greske = array(
							  UPLOAD_ERR_OK=> "Datoteka je uspješno predana",
							  UPLOAD_ERR_INI_SIZE  => "Datoteka je prevelika",
							  UPLOAD_ERR_FORM_SIZE => "Datoteka je prevelika",
							  UPLOAD_ERR_PARTIAL => "Partial upload.",
							  UPLOAD_ERR_NO_FILE => "Niste predali datoteku",
							  UPLOAD_ERR_NO_TMP_DIR => "Greška sa serverom",
							  UPLOAD_ERR_CANT_WRITE => "Greška sa serverom",
							  UPLOAD_ERR_EXTENSION=> "Greška vezana uz ekstenziju datoteke."
							);
							if ($greska>0) {
							 Form::setError("noviKorisnik", $upload_greske[$greska]);	  
							} else {
								 //najprije ćemo dohvatiti tmp_name slike- privremeni naziv datoteke na serveru
								  $privremena_datoteka=$_FILES['slika']['tmp_name'];
								  //dohvaćanje stvarnog naziva slike- kako se slika zvala kad ju je korisnik predavao
								  $datoteka_spremanja=basename($_FILES['slika']['name']);
								  
								  //SREĐIVANJE IMENA SLIKE ZA SPREMANJE NA SERVERU I U BAZU PODATAKA
								  
								  //tebamo predvidjeti da nam korisnik može predati datoteku koja ima u nazivu više točaka
								  //nama je potrebna samo zadnja točka i ono što slijedi iza nje, a to je ekstenzija datoteke
								  //tražimo zadnju točku sa strrpos, i njezinu poziciju spremamo u varijablu
								  $posljednjaTocka = strrpos($datoteka_spremanja, ".");
								  $ekstenzija= substr($datoteka_spremanja, $posljednjaTocka);
								  //brisanje svih točaka od početka naziva do zadnje točke
								  $datoteka_spremanja= str_replace(".", "", substr($datoteka_spremanja, 0, $posljednjaTocka));
								  //micanje_razmaknica
								  $datoteka_spremanja= str_replace(" ", "", $datoteka_spremanja);
								  //skrati naslov do 50 znakova ako ima više od 50 znakova
								  if (strlen($datoteka_spremanja)>50) $datoteka_spremanja= substr($datoteka_spremanja, 0, 50);
								  //vraćanje ekstenzije
								  $datoteka_spremanja.=$ekstenzija;
								  
								  //naziv foldera na serveru, putanja do njega, gdje će se slike spremati
								  $upload_dir="slike";
									  
								   //PROVJERA DA LI DATOTEKA S ISTIM NAZIVOM VEĆ NE POSTOJI
								  //provijeriti da li datoteka s navedenim nazivom već postoji, s funkcijom file_exists
								  //ako datoteka postoji u folderu slike novu ćemo spremiti s dodatkom broja
								  //provjeravamo tako dugo dok ne dobijemo da datoteka s tim nazivom ne postoji
									$i=0;
									while (file_exists($upload_dir."/".$datoteka_spremanja)) {
								  //uzimamo naziv datoteke i odvajamo ekstenziju i spremamo u zasebne varijable
									  list ($naziv, $ekstenzija)=explode(".", $datoteka_spremanja);
								  //pomoću rtrim brišemo posljednji broj koji je bio dodan na kraj naziva i dodajemo novi broj i ekstenziju
									  $datoteka_spremanja=rtrim($naziv, strval($i-1)) . $i . "." . $ekstenzija;
									  $i++;
								}
									//premiještanje datoteke iz privremenog foldera u folder slike, i dajemo joj naziv kako smo ga oblikovali
								//ukoliko uspješno prebacimo sliku idemo ju pripremiti za prikaz na stranici
								$slika=$upload_dir. "/" . $datoteka_spremanja;
									if (move_uploaded_file($privremena_datoteka, $slika)) {
									//funkcija image_resize je definirana u datoteci crop.php
									//Ona nam služi za promjenu veličine i formata datoteke
									//funkcija će vratiti true ukoliko uspješno obavi svoj zadatak, a u ostalim slučajevima vraća poruku pogreške
									//pošto vraća poruku, a neki string ako sadrži tekst je true, provjeru moramo raditi sa !== jer bi trebalo biti identično
									//parametri koje prosljeđujemo funkciji; datoteka koju želimo preoblikovati, kamo ćemo spremiti preoblikovanu datoteku, širina, visina, crop- da li ćemo obrezati sliku
											if (true !== ($greska_sa_slikom= image_resize($slika, $slika, 200, 200, 1))) {
									  //ako ne uspijemo preoblikovati sliku radimo brisanje slike iz foldera
											 unlink($slika);
											} else {
										  	//upisivanje u bazu
												  $izjava=$baza->prepare("INSERT INTO korisnici SET email=?, korisnik=?, lozinka=?, slika=?");
												  $izjava->bind_param('ssss',$email, $korisnik, $lozinka, $datoteka_spremanja);
												  
												  if ($izjava->execute()) {
													echo '<div class="alert alert-success">
																		<strong>Korisnik je uspješno upisan u bazu podataka</strong>
														</div>';
												} else {
													Form::setError("noviKorisnik", "Pogreška s upisivanjem u bazu podataka");
												}
											}
									} else {
									 Form::setError("noviKorisnik", "Slika nije prebačena u folder na serveru");
								  }
								}
								
							}
						}
						
					} else {
						Form::setError("noviKorisnik", "Pogreška s upisivanjem u bazu podataka");
					}		
					$baza->close();
		}
			else {
				Form::setError("noviKorisnik", "Lozinke se ne podudaraju.");
				}
		
	}

	}
	
	
	Form::open ('noviKorisnik', '', array("enctype"=>"multipart/form-data"));
	Form::Hidden ('predano', 'da');
	Form::File("Avatar", "slika", array ("required" => 1));
	Form::Textbox ("Korisnik:", "korisnik", array(
		"required" => 1,
		"validation" => new Validation_RegExp ("/^[a-zA-Z0-9\._\-]{5,50}$/", "%element% mora sadržavati samo brojke i slova te -, _ i .. Minimalan broj znakova je 5.")																		 
																				 ));
	Form::Email("Email adresa:", "email", array(
    "required" => 1,

));
	 Form::Password("Lozinka:", "lozinka", array(
		"required" => 1,
		"validation" => new Validation_RegExp ("/^[a-zA-Z0-9\._\-]{6,40}$/", "%element% mora sadržavati samo brojke i slova te -, _ i .. Minimalan broj znakova je 6.")																		 
																				 ));
	 Form::Password("Ponovite lozinku:", "lozinka2", array(
		"required" => 1		  
																						  ));
	Form::Button('Kreiraj korisnika');
	Form::close (false);
	echo "</div>";
	include('footer.php');
?>

