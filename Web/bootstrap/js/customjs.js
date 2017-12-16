$(document).ready(function(){
    $("[data-toggle='tooltip']").tooltip();   
});




$.post('TypeaHead.php',function(data){
	
	$('#search').attr('data-source',data);
	});


 function isci(){
	
	var naslov = document.getElementById("search");
	var nes = naslov.value;
	window.location.href = "popis.php?naslov="+nes;
	//console.log(naslov);
	//console.log("hej");
	//alert(naslov);
	//return false;
	
}