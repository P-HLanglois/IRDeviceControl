

function startTV() {
  $("#tvButton").prop("disabled",true);
  const Http = new XMLHttpRequest();
  const url='http://192.168.43.116/startTV';
  Http.open("GET", url);
  Http.setRequestHeader('Access-Control-Allow-Headers', '*');
  Http.send();
  Http.onreadystatechange=(e)=>{
    console.log(Http.responseText);
    $("#tvButton").prop("disabled",false);
  }
}

function throwOnOffVideoProj() {
  $("#retroButton").prop("disabled",true);
  const Http = new XMLHttpRequest();
  const url='http://192.168.43.116/signalOnOffVideoProj';
  Http.open("GET", url);
  Http.setRequestHeader('Access-Control-Allow-Headers', '*');
  Http.send();
  Http.onreadystatechange=(e)=>{
    console.log(Http.responseText);
    $("#retroButton").prop("disabled",false);
  }
}
