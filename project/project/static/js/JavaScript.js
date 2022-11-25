var modal =  document.getElementsByClassName('modal')[0] ;
var positionVar = 100;
var temp= positionVar;
var flag = 7000 ; // this number is for auto mode to be started
$(document).ready(function(){
////// codes for changing the position \\\\\

	$(".lowBtn , .hiBtn , .arrow").on('click' , function(event){
		$(".syncInput").slideDown(200);
		if($(event.target).attr('class') == 'lowBtn btn item2' || $(event.target).attr('class') == 'left arrow'){
			if(temp != 0 ){
				temp = temp - 5 ;
				$(".syncInput").val(temp);
				console.log($(event.target).attr('class'));
			}
			else{
				$(".syncInput").val('kidding me right?!');
			}
		}
		else if($(event.target).attr('class') == 'hiBtn btn item4' || $(event.target).attr('class') == 'right arrow'){
			if(temp != 100 ){
				temp = temp + 5 ;
				$(".syncInput").val(temp);
				console.log($(event.target).attr('class'));
			}
			else{
				$(".syncInput").val('No way man!');
			}
		}
	});
	$(".go").click(function(){
		var desiredPosition = $(".syncInput").val();
		$.getJSON( '/_positionGet' ,
		{'position' : desiredPosition},
		function(data){
			$(".progress").animate({ width: data.position+'%'});
			$(".syncInput").slideUp(200).val('');
			$("#percent").text(data.position+'%');
			console.log('hey');
		});
	});
	
	$(window).click(function(event){
	console.log($(event.target).attr('class'));
	var className = $(event.target).attr('class') ;
	if(className !='lowBtn btn item2' && className !='hiBtn btn item4' && className !='btn go item3' && className !='left arrow' && className != 'right arrow' && className != 'syncInput'){
			temp = positionVar;
			$(".syncInput").slideUp(200).val('');
			console.log($(event.target).attr('class'));
		}
	});

////// end of the codes for changing the position \\\\\\\

/////// the codes for auto mode \\\\\\

	$(".slider").click(function(){
		if (flag == 7000){
			flag = 6000;
		}else{
			flag = 7000;
		}
		$.ajax({
		url: '/_auto',
		data: JSON.stringify({'state': flag}),
		type: "POST",
		contentType: "application/json"
		}
		);
	}
	);


////// end of the codes for auto mode \\\\\


////// the codes for scadule functionality \\\\\\\
	
	$('.item5').click(function(){
		$('.modal').show(500);
	});
	$('.close').click(function(){
  		$('.modal').hide(500);
  		$('.flash').hide();
  		$(".scaduleDoneMessage").slideUp(400);
	});
	$(window).click(function(event){
  		if(event.target == modal){
    		$('.modal').hide(500);
    		$('.flash').hide();
    		$(".scaduleDoneMessage").slideUp(400);
  		}
	});	
	$(".scaduleForm").submit(function(event){
		event.preventDefault();
		//console.log(openTime);
		//console.log(closeTime);
		$.ajax({
			url : '/_scadule',
			type: 'POST',
			data:{"openTime" : $('[name="openTime"]').val() , "closeTime" : $('[name="closeTime"]').val() },
		}).done(function(data){
			if (data.error){
				$('.scaduleDoneMessage').text('Sorry! Try again :(').show(400);
			}
			else{
				$(".scaduleDoneMessage").text('Done :)').slideDown(500);
				$('.flash').css({'display':'block'});
			}
		});
		
	});
/////// end of the codes for scadule functionality
});

