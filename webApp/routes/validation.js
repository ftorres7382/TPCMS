// Nombre de Estudiante: Eliud Perez
// Numero de Estudiante: Y00522390
// Curso: COMP-2025 - Desarrollo de Páginas Web
// Lab 4 - Página Web con forms y Javascript.
// Fecha de Entrega: 31 de Octubre de 2019
// Descripción: Este programa crea una página web HTML
// añadiendo al lab pasado un form para que el usuario añada
// su información a la pagina



function changeColor(color){

    document.body.style.background = color;

  }


function validateForm(){

var valueField = document.forms["myform"]["firstname"].value;
if (valueField == ""){
  alert("First name field is empty put something in.Try again");
  return false;
  }

valueField = document.forms["myform"]["Last name"].value;

    if (valueField == ""){
      alert("Last name field is empty put something in.Try again");
      return false;
      }

valueField = document.forms["myform"]["email"].value;

   if (valueField == ""){
      alert("Email field is empty. Try again");
      return false;
      }
 valueField = document.forms["myform"]["password"].value;
 if (valueField == ""){
    alert("Password field is empty. Try again");
    return false;
    }
}


function checkBox(option){
  var checkbox;
  if (option == 1){
      checkbox = document.getElementByID("C++");
  }
  if (option == 2){
      checkbox = document.getElementByID("JS");
  }
  if (option == 3){
      checkbox = document.getElementByID("Java");
  }
  if (option == 4){
      checkbox = document.getElementByID("Python");
  }
  if (option == 5){
      checkbox = document.getElementByID("C");
  }

  if(checkBox.checked == true){
    alert("CheckBox = Checked Value = " + checkBox.value);
  }
  else {
    alert("Unchecked.")
  }

}

function validateNumber(){
  var x, text;

  x = document.getElementByID("celnum").value;

  if(isNan(x) || x < 1){
    text = "Input not valid";
    alert("Input a number or a positive number.")
  }
  else
  text="Input is valid.";
  alert(text);

}


function saveDataLocally(){
alert("Entro!")
if (typeof(Storage) !== "undefined"){

var gender = document.forms["myform"]["gender"];
var genderValue = "@";


  for(var i = 0; i < gender.length ; i++){
      if(gender[i].checked){
        genderValue = gender[i].value;
      }
    }
localStorage.setItem("firstname", document.forms["myform"]["firstname"].value);
localStorage.setItem("Last name", document.forms["myform"]["Last name"].value);
localStorage.setItem("email", document.forms["myform"]["email"].value );
localStorage.setItem("password",document.forms["myform"]["password"].value );
localStorage.setItem("gender", genderValue.toUpperCase());

document.getElementByID("saveDataLocally").innerHTML =
localStorage.getItem("firstname")
+ ","
+localStorage.getItem("Last name")
+","
+localStorage.getItem("email")
+","
+localStorage.getItem("password")
+","
+localStorage.getItem("gender")
+"...";

}


}
