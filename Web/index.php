<?php 
include("php/sesija.php");
?>
<!DOCTYPE html>
<html lang="en">

  <head>

    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>Poker</title>

    <!-- Bootstrap core CSS -->
    <link href="vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">

    <!-- Custom fonts for this template -->
    <link href="vendor/font-awesome/css/font-awesome.min.css" rel="stylesheet" type="text/css">
    <link href="https://fonts.googleapis.com/css?family=Montserrat:400,700" rel="stylesheet" type="text/css">
    <link href="https://fonts.googleapis.com/css?family=Lato:400,700,400italic,700italic" rel="stylesheet" type="text/css">

    <!-- Plugin CSS -->
    <link href="vendor/magnific-popup/magnific-popup.css" rel="stylesheet" type="text/css">

    <!-- Custom styles for this template -->
    <link href="css/myCss.css" rel="stylesheet">
	<link href="css/loginCss.css" rel="stylesheet">
  </head>

  <body id="page-top">

    <!-- Navigation -->
    <nav class="navbar navbar-expand-lg bg-secondary fixed-top text-uppercase" id="mainNav">
      <div class="container">
        <a class="navbar-brand js-scroll-trigger" href="#page-top">Poker</a>
        <button class="navbar-toggler navbar-toggler-right text-uppercase bg-primary text-white rounded" type="button" data-toggle="collapse" data-target="#navbarResponsive" aria-controls="navbarResponsive" aria-expanded="false" aria-label="Toggle navigation">
          Menu
          <i class="fa fa-bars"></i>
        </button>
        <div class="collapse navbar-collapse" id="navbarResponsive">
          <ul class="navbar-nav ml-auto">
            <li class="nav-item mx-0 mx-lg-1">
              <a class="nav-link py-3 px-0 px-lg-3 rounded js-scroll-trigger" href="#portfolio">Card power</a>
            </li>
            <li class="nav-item mx-0 mx-lg-1">
              <a class="nav-link py-3 px-0 px-lg-3 rounded js-scroll-trigger" href="#about">Rules</a>
            </li>
			
			<?php
			if(isset($_SESSION['korisnik'])):
			?>
				<li class="nav-item mx-0 mx-lg-1"><a style="text-decoration:false;" href="php/profil.php" class=" nav-link py-3 px-0 px-lg-3 ">Profile</a></li>
				<li class="nav-item mx-0 mx-lg-1"><a style="text-decoration:false;" href="php/logout.php" class=" nav-link py-3 px-0 px-lg-3 ">Log out</a></li>
			<?php else : ?>
			<li class="nav-item mx-0 mx-lg-1"><a style="text-decoration:false;" href="php/login.php" class=" nav-link py-3 px-0 px-lg-3 ">Login</a></li>
			<?php endif;   ?>
          </ul>
        </div>
      </div>
    </nav>

    <!-- Header -->
    <header class="masthead bg-primary text-white text-center">
      <div class="container">
        <img class="img-fluid mb-5 d-block mx-auto" src="img/pokerLogo.png" alt="">
        <h1 class="text-uppercase mb-0"> Welcome to Poker</h1>
        <hr class="star-light">
       
      </div>
    </header>

    <!-- Portfolio Grid Section -->
    <section class="portfolio" id="portfolio">
      <div class="container">
        <h2 class="text-center text-uppercase text-secondary mb-0">Card power</h2>
        <hr class="star-dark mb-5">
        <div class="row">
          <div class="col-md-6 col-lg-4">
            <a class="portfolio-item d-block mx-auto" href="#portfolio-modal-1">
              <div class="portfolio-item-caption d-flex position-absolute h-100 w-100">
                <div class="portfolio-item-caption-content my-auto w-100 text-center text-white">
                  <i class="fa fa-question-circle fa-3x"></i>
                </div>
              </div>
              <img style="text-align:center;" class="img-fluid" src="img/portfolio/onePair.png" alt="">
            </a>
          </div>
          <div class="col-md-6 col-lg-4">
            <a class="portfolio-item d-block mx-auto" href="#portfolio-modal-2">
              <div class="portfolio-item-caption d-flex position-absolute h-100 w-100">
                <div class="portfolio-item-caption-content my-auto w-100 text-center text-white">
                  <i class="fa fa-question-circle fa-3x"></i>
                </div>
              </div>
              <img class="img-fluid" src="img/portfolio/twoPairs.png" alt="">
            </a>
          </div>
          <div class="col-md-6 col-lg-4">
            <a class="portfolio-item d-block mx-auto" href="#portfolio-modal-3">
              <div class="portfolio-item-caption d-flex position-absolute h-100 w-100">
                <div class="portfolio-item-caption-content my-auto w-100 text-center text-white">
                  <i class="fa fa-question-circle fa-3x"></i>
                </div>
              </div>
              <img class="img-fluid" src="img/portfolio/threeOfAKind.png" alt="">
            </a>
          </div>
          <div class="col-md-6 col-lg-4">
            <a class="portfolio-item d-block mx-auto" href="#portfolio-modal-4">
              <div class="portfolio-item-caption d-flex position-absolute h-100 w-100">
                <div class="portfolio-item-caption-content my-auto w-100 text-center text-white">
                  <i class="fa fa-question-circle fa-3x"></i>
                </div>
              </div>
              <img class="img-fluid" src="img/portfolio/straight.png" alt="">
            </a>
          </div>
          <div class="col-md-6 col-lg-4">
            <a class="portfolio-item d-block mx-auto" href="#portfolio-modal-5">
              <div class="portfolio-item-caption d-flex position-absolute h-100 w-100">
                <div class="portfolio-item-caption-content my-auto w-100 text-center text-white">
                  <i class="fa fa-question-circle fa-3x"></i>
                </div>
              </div>
              <img class="img-fluid" src="img/portfolio/flush.png" alt="">
            </a>
          </div>
          <div class="col-md-6 col-lg-4">
            <a class="portfolio-item d-block mx-auto" href="#portfolio-modal-6">
              <div class="portfolio-item-caption d-flex position-absolute h-100 w-100">
                <div class="portfolio-item-caption-content my-auto w-100 text-center text-white">
                  <i class="fa fa-question-circle fa-3x"></i>
                </div>
              </div>
              <img class="img-fluid" src="img/portfolio/fullHouse.png" alt="">
            </a>
          </div>
		           <div class="col-md-6 col-lg-4">
            <a class="portfolio-item d-block mx-auto" href="#portfolio-modal-7">
              <div class="portfolio-item-caption d-flex position-absolute h-100 w-100">
                <div class="portfolio-item-caption-content my-auto w-100 text-center text-white">
                  <i class="fa fa-question-circle fa-3x"></i>
                </div>
              </div>
              <img class="img-fluid" src="img/portfolio/poker.png" alt="">
            </a>
          </div>
          <div class="col-md-6 col-lg-4">
            <a class="portfolio-item d-block mx-auto" href="#portfolio-modal-8">
              <div class="portfolio-item-caption d-flex position-absolute h-100 w-100">
                <div class="portfolio-item-caption-content my-auto w-100 text-center text-white">
                  <i class="fa fa-question-circle fa-3x"></i>
                </div>
              </div>
              <img class="img-fluid" src="img/portfolio/straightFlush.png" alt="">
            </a>
          </div>
          <div class="col-md-6 col-lg-4">
            <a class="portfolio-item d-block mx-auto" href="#portfolio-modal-9">
              <div class="portfolio-item-caption d-flex position-absolute h-100 w-100">
                <div class="portfolio-item-caption-content my-auto w-100 text-center text-white">
                  <i class="fa fa-question-circle fa-3x"></i>
                </div>
              </div>
              <img class="img-fluid" src="img/portfolio/royalFlush.png" alt="">
            </a>
          </div>
        </div>
      </div>
    </section>

    <!-- About Section -->
    <section class="bg-primary text-white mb-0" id="about">
      <div class="container">
        <h2 class="text-center text-uppercase text-white">Poker rules</h2>
        <hr class="star-light mb-5">
        <div class="row">
          <div class="col-lg-4 ml-auto">
            <p class="lead">Typically, the winner of each hand of poker is the player that holds the highest ranked hand when all cards are shown at the end of the hand –known as the ‘showdown’ – or the player that makes the last uncalled bet, thus winning without needing to reach a showdown.</p>
          </div>
          <div class="col-lg-4 mr-auto">
            <p class="lead">After any initial cards are dealt, players are usually called upon to act in turn, moving clockwise around the table. Each player can usually take one of the following actions when it is their turn to act: Check, Bet, Fold ,Call, Raise</p>
          </div>

        </div>
        <div class="text-center mt-4">
        <h5 style="text-align:justify;">Check – To check is to decline the opportunity to open the betting. Players can only check when there is no bet during the current round, and the act of checking passes the action clockwise to the next person in the hand. If all active players check, those players remain in the hand and the round is considered complete.<br /> <br />
Bet – Players may bet if no other players have bet during the current round. Once a bet has been made, other players must ‘call’ by matching the amount bet, in order to remain in the hand.<br /><br />
Fold – Players who fold forfeit their cards and cannot win or act again during the current hand.<br /><br />
Call – Players can call if other players have bet during the current round; this requires the calling player to match the highest bet made.<br /><br />
Raise – Players may raise if other players have bet during the current round; this requires the raising player to match the highest bet made, and then make a greater one. All subsequent players are required to call the raise or raise again (‘re-raise’) to stay in the hand.</h5>
        </div>
      </div>
    </section>



    <!-- Footer -->


    <div class="copyright py-4 text-center text-white">
      <div class="container">
        <small>Copyright &copy; Poker 2017</small>
      </div>
    </div>

    <!-- Scroll to Top Button (Only visible on small and extra-small screen sizes) -->
    <div class="scroll-to-top d-lg-none position-fixed ">
      <a class="js-scroll-trigger d-block text-center text-white rounded" href="#page-top">
        <i class="fa fa-chevron-up"></i>
      </a>
    </div>

    <!-- Portfolio Modals -->

    <!-- Portfolio Modal 1 -->
    <div class="portfolio-modal mfp-hide" id="portfolio-modal-1">
      <div class="portfolio-modal-dialog bg-white">
        <a class="close-button d-none d-md-block portfolio-modal-dismiss" href="#">
          <i class="fa fa-3x fa-times"></i>
        </a>
        <div class="container text-center">
          <div class="row">
            <div class="col-lg-8 mx-auto">
              <h2 class="text-secondary text-uppercase mb-0">One pair</h2>
              <hr class="star-dark mb-5">
              <img class="img-fluid mb-5" src="img/info/infoPair.png" alt="">
              <h4 class="mb-5"> Two cards of a matching rank, and three unrelated side cards.</h4>
			  <p class="mb-5">In the event of a tie: Highest pair wins. If players have the same pair, the highest side card wins, and if necessary, the second-highest and third-highest side card can be used to break the tie.</p>
              <a class="btn btn-primary btn-lg rounded-pill portfolio-modal-dismiss" href="#">
                <i class="fa fa-close"></i>
                Close </a>
            </div>
          </div>
        </div>
      </div>
    </div>

    <!-- Portfolio Modal 2 -->
    <div class="portfolio-modal mfp-hide" id="portfolio-modal-2">
      <div class="portfolio-modal-dialog bg-white">
        <a class="close-button d-none d-md-block portfolio-modal-dismiss" href="#">
          <i class="fa fa-3x fa-times"></i>
        </a>
        <div class="container text-center">
          <div class="row">
            <div class="col-lg-8 mx-auto">
              <h2 class="text-secondary text-uppercase mb-0">Two pairs</h2>
              <hr class="star-dark mb-5">
              <img class="img-fluid mb-5" src="img/info/infoTwoPairs.png" alt="">
              <h4 class="mb-5">Two cards of a matching rank, another two cards of a different matching rank, and one side card.</h4>
              <p class="mb-5">In the event of a tie: Highest pair wins. If players have the same highest pair, highest second pair wins. If both players have two identical pairs, highest side card wins.</p>
			  <a class="btn btn-primary btn-lg rounded-pill portfolio-modal-dismiss" href="#">
                <i class="fa fa-close"></i>
                Close</a>
            </div>
          </div>
        </div>
      </div>
    </div>

    <!-- Portfolio Modal 3 -->
    <div class="portfolio-modal mfp-hide" id="portfolio-modal-3">
      <div class="portfolio-modal-dialog bg-white">
        <a class="close-button d-none d-md-block portfolio-modal-dismiss" href="#">
          <i class="fa fa-3x fa-times"></i>
        </a>
        <div class="container text-center">
          <div class="row">
            <div class="col-lg-8 mx-auto">
              <h2 class="text-secondary text-uppercase mb-0">Three of a kind</h2>
              <hr class="star-dark mb-5">
              <img class="img-fluid mb-5" src="img/info/infoThreeOfAKind.png" alt="">
              <h4 class="mb-5">Three cards of the same rank, and two unrelated side cards.</h4>
              <p class="mb-5">In the event of a tie: Highest ranking three of a kind wins. In community card games where players have the same three of a kind, the highest side card, and if necessary, the second-highest side card wins.</p>
			  <a class="btn btn-primary btn-lg rounded-pill portfolio-modal-dismiss" href="#">
                <i class="fa fa-close"></i>
                Close</a>
            </div>
          </div>
        </div>
      </div>
    </div>

    <!-- Portfolio Modal 4 -->
      <div class="portfolio-modal mfp-hide" id="portfolio-modal-4">
      <div class="portfolio-modal-dialog bg-white">
        <a class="close-button d-none d-md-block portfolio-modal-dismiss" href="#">
          <i class="fa fa-3x fa-times"></i>
        </a>
        <div class="container text-center">
          <div class="row">
            <div class="col-lg-8 mx-auto">
              <h2 class="text-secondary text-uppercase mb-0">Straight</h2>
              <hr class="star-dark mb-5">
              <img class="img-fluid mb-5" src="img/info/infoStraight.png" alt="">
              <h4 class="mb-5">Five cards in sequence.</h4>
              <p class="mb-5">In the event of a tie: Highest ranking card at the top of the sequence wins.
Note: The Ace may be used at the top or bottom of the sequence, and is the only card which can act in this manner. A,K,Q,J,T is the highest (Ace high) straight; 5,4,3,2,A is the lowest (Five high) straight.</p>
			  <a class="btn btn-primary btn-lg rounded-pill portfolio-modal-dismiss" href="#">
                <i class="fa fa-close"></i>
                Close</a>
            </div>
          </div>
        </div>
      </div>
    </div>

    <!-- Portfolio Modal 5 -->
    <div class="portfolio-modal mfp-hide" id="portfolio-modal-5">
      <div class="portfolio-modal-dialog bg-white">
        <a class="close-button d-none d-md-block portfolio-modal-dismiss" href="#">
          <i class="fa fa-3x fa-times"></i>
        </a>
        <div class="container text-center">
          <div class="row">
            <div class="col-lg-8 mx-auto">
              <h2 class="text-secondary text-uppercase mb-0">Flush</h2>
              <hr class="star-dark mb-5">
              <img class="img-fluid mb-5" src="img/info/infoFlush.png" alt="">
              <h4 class="mb-5">Five cards of the same suit.</h4>
              <p class="mb-5">In the event of a tie: The player holding the highest ranked card wins. If necessary, the second-highest, third-highest, fourth-highest, and fifth-highest cards can be used to break the tie. If all five cards are the same ranks, the pot is split. The suit itself is never used to break a tie in poker.</p>
			  <a class="btn btn-primary btn-lg rounded-pill portfolio-modal-dismiss" href="#">
                <i class="fa fa-close"></i>
                Close</a>
            </div>
          </div>
        </div>
      </div>
    </div>

    <!-- Portfolio Modal 6 -->
     <div class="portfolio-modal mfp-hide" id="portfolio-modal-6">
      <div class="portfolio-modal-dialog bg-white">
        <a class="close-button d-none d-md-block portfolio-modal-dismiss" href="#">
          <i class="fa fa-3x fa-times"></i>
        </a>
        <div class="container text-center">
          <div class="row">
            <div class="col-lg-8 mx-auto">
              <h2 class="text-secondary text-uppercase mb-0">Full house</h2>
              <hr class="star-dark mb-5">
              <img class="img-fluid mb-5" src="img/info/infoFullHouse.png" alt="">
              <h4 class="mb-5">Three cards of the same rank, and two cards of a different, matching rank.</h4>
              <p class="mb-5">In the event of a tie: Highest three matching cards wins the pot. In community card games where players have the same three matching cards, the highest value of the two matching cards wins.</p>
			  <a class="btn btn-primary btn-lg rounded-pill portfolio-modal-dismiss" href="#">
                <i class="fa fa-close"></i>
                Close</a>
            </div>
          </div>
        </div>
      </div>
    </div>
	
	     <div class="portfolio-modal mfp-hide" id="portfolio-modal-7">
      <div class="portfolio-modal-dialog bg-white">
        <a class="close-button d-none d-md-block portfolio-modal-dismiss" href="#">
          <i class="fa fa-3x fa-times"></i>
        </a>
        <div class="container text-center">
          <div class="row">
            <div class="col-lg-8 mx-auto">
              <h2 class="text-secondary text-uppercase mb-0">Four of a kind</h2>
              <hr class="star-dark mb-5">
              <img class="img-fluid mb-5" src="img/info/infoPoker.png" alt="">
              <h4 class="mb-5">Four cards of the same rank, and one side card or ‘kicker’.</h4>
              <p class="mb-5">In the event of a tie: Highest four of a kind wins. In community card games where players have the same four of a kind, the highest fifth side card ('kicker') wins.</p>
			  <a class="btn btn-primary btn-lg rounded-pill portfolio-modal-dismiss" href="#">
                <i class="fa fa-close"></i>
                Close</a>
            </div>
          </div>
        </div>
      </div>
    </div>
	
	     <div class="portfolio-modal mfp-hide" id="portfolio-modal-8">
      <div class="portfolio-modal-dialog bg-white">
        <a class="close-button d-none d-md-block portfolio-modal-dismiss" href="#">
          <i class="fa fa-3x fa-times"></i>
        </a>
        <div class="container text-center">
          <div class="row">
            <div class="col-lg-8 mx-auto">
              <h2 class="text-secondary text-uppercase mb-0">Straight flush</h2>
              <hr class="star-dark mb-5">
              <img class="img-fluid mb-5" src="img/info/infoStraightFlush.png" alt="">
              <h4 class="mb-5">Five cards in numerical order, all of identical suits.</h4>
              <p class="mb-5">In the event of a tie: Highest rank at the top of the sequence wins.
The best possible straight flush is known as a royal flush, which consists of the ace, king, queen, jack and ten of a suit. A royal flush is an unbeatable hand.</p>
			  <a class="btn btn-primary btn-lg rounded-pill portfolio-modal-dismiss" href="#">
                <i class="fa fa-close"></i>
                Close</a>
            </div>
          </div>
        </div>
      </div>
    </div>
	
	     <div class="portfolio-modal mfp-hide" id="portfolio-modal-9">
      <div class="portfolio-modal-dialog bg-white">
        <a class="close-button d-none d-md-block portfolio-modal-dismiss" href="#">
          <i class="fa fa-3x fa-times"></i>
        </a>
        <div class="container text-center">
          <div class="row">
            <div class="col-lg-8 mx-auto">
              <h2 class="text-secondary text-uppercase mb-0">Royal flush</h2>
              <hr class="star-dark mb-5">
              <img class="img-fluid mb-5" src="img/info/infoRoyalFlush.png" alt="">
              <h4 class="mb-5">Five cards in numerical order, all of identical suits.</h4>
              <p class="mb-5">In the event of a tie: Highest rank at the top of the sequence wins.
The best possible straight flush is known as a royal flush, which consists of the ace, king, queen, jack and ten of a suit. A royal flush is an unbeatable hand.</p>
			  <a class="btn btn-primary btn-lg rounded-pill portfolio-modal-dismiss" href="#">
                <i class="fa fa-close"></i>
                Close</a>
            </div>
          </div>
        </div>
      </div>
    </div>

    <!-- Bootstrap core JavaScript -->
    <script src="vendor/jquery/jquery.min.js"></script>
    <script src="vendor/bootstrap/js/bootstrap.bundle.min.js"></script>

    <!-- Plugin JavaScript -->
    <script src="vendor/jquery-easing/jquery.easing.min.js"></script>
    <script src="vendor/magnific-popup/jquery.magnific-popup.min.js"></script>

  

    <!-- Custom scripts for this template -->
    <script src="js/myJS.js"></script>

  </body>

</html>
