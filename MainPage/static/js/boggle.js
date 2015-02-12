$(document).ready(function () {

  $(function() {
    $("#boggleInput1").focus();
  });

  $('.boggleBoard-answer').hide();

  $("input[id^='boggleInput']").keyup(function(e){
      if($(this).val().length==1)
      { 
        var nextInt = (parseInt($(this).context.id.split("boggleInput")[1]) + 1);
        $('#boggleInput'+ (nextInt-1)).removeClass("glowing-border !important")
        $("#boggleInput"+nextInt).focus();
      }
        
    })

  /* data validation inside createplan modal and display saveplan button*/
  $("#generate").click(function(){

    if(checkLetters())
    {
      boggleLetters = getLetters()
        $.ajax({                              //ajax call for validating if planname already exist
         type:"POST",
         url:"/index/",
         data: {
                'boggleLetter': boggleLetters,   
                'operation': 'generateWords',
                },
         success: function(response){
                populateAnswerList(response)
         }
      });
    }
    else
    {

    }
  });

  $("#reset").click(function(){
      for(var i = 1; i < 17; i++) {
        $("#boggleInput"+i).val("");
        $('#boggleInput'+i).removeClass("glowing-border !important")
      }
      $("#boggleInput1").focus();
  });
});


function checkLetters()
{
  var valid = true;
  for(var i = 1; i < 17; i++) { 
    var character = $("#boggleInput"+i).val().trim().toLowerCase();
    if(/^[a-z]$/.exec(character) == null)
    {
      $('#boggleInput'+i).addClass("glowing-border !important")
      valid = false;
    }
    else
    {
      $('#boggleInput'+i).removeClass("glowing-border !important")
    }
  }
  console.log(valid)
  return valid;
}

function getLetters()
{
  var boggleLetters ="";
  for(var i = 1; i < 17; i++) {
    boggleLetters += $("#boggleInput"+i).val().trim().toLowerCase()
  }
  return boggleLetters;
}

function populateAnswerList(response)
{
  $('.boggleBoard-answer').show();
  $("#list1").empty()
  $("#list2").empty()
  $("#list3").empty()

console.log(response.length)
  if(response.length == 1 && response[0] == '')
  {
    response[0] = "No words found! :("
  }
  for(i = 0; i < response.length; i++)
  {
    if(response[i] != "")
    {
      if(i%2 == 0)
        $("#list"+((i%3)+1)).append('<li class="list-group-item" style="background-color: #FFF;"">'+ response[i] +'</li>');  
      else
        $("#list"+((i%3)+1)).append('<li class="list-group-item" style="background-color: #FFB;">'+ response[i] +'</li>');  
    }
      
  }
}