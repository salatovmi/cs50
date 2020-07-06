function check_form()
{
    var isFormValid = true;

    $(".form-control").each(function(){
        if ($(this).val().length == 0){
            $(this).addClass("highlight");
            isFormValid = false;
            $(this).siblings(".form_error").removeClass("hidden");
        }
        else{
            $(this).removeClass("highlight");
            $(this).siblings(".form_error").addClass("hidden");
        }
    });

    return isFormValid;
}

function check_symbol()
{
    var isFilled = true;

    if ($("#symbol").val().length == 0){
        $(this).addClass("highlight");
        isFilled = false;
        $("#symbol_error").removeClass("hidden");
    }

    return isFilled;
}

function check_registraion_form()
{
    var isFormValid = check_form();

    if ($("#password").val() !== $("#repeat_password").val()){
        isFormValid = false;
        $("#repeat_error").removeClass("hidden");
    }

    return isFormValid;
}

function check_login()
{
    var isFormValid = check_form();

    $(".wrong_creds").each(function(){
        $(this).addClass("hidden");
    });

    return isFormValid;
}

function check_buy_from()
{
    var isFormValid = check_form();

    if ($("#shares").val() < 1){
        isFormValid = false;
        $("#shares_error").removeClass("hidden");
    }

    return isFormValid;
}

function check_sell_from()
{
    var isFormValid = check_form();

    if ($("#shares").val() < 1){
        isFormValid = false;
        $("#shares_error").removeClass("hidden");
    }

    if ($("#symbol").val() == "Default"){
        isFormValid = false;
        $("#symbol_error").removeClass("hidden");
    }

    return isFormValid;
}