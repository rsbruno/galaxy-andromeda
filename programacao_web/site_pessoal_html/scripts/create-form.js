const email = document.getElementById('emailAdress');
const firstName = document.getElementById('firstName');
const phone = document.getElementById('phoneNumber');
const country = document.getElementById('country');
const state = document.getElementById("state")
const adrress = document.getElementById("address")

function emailErrors(em) {
    const errors = []
    if (em.value == 0)
        errors.push("Você precisa de um email")
    if (!em.value.includes("@") && (!em.value == 0))
        errors.push("Seu email deve conter '@'")
    if (errors.length > 0)
        renderErrors(errors, "email", "em")
}

function validateForm() {
    removeErrors("ft-name")
    removeErrors("lt-name")
    removeErrors("phone")
    removeErrors("em")
    removeErrors("ct-country")
    removeErrors("id-state")
    removeErrors("id-address")

    if (firstName.value == 0)
        renderErrors([
            ["Precisamos saber seu nome"]
        ], "ft-name", "ft-name")
    if (lastName.value == 0)
        renderErrors([
            ["Precisamos saber seu nome completo"]
        ], "lt-name", "lt-name")

    if (phone.value == 0)
        renderErrors([
            ["Informe seu telefone"]
        ], "phone", "phone")

    if (country.value == 0)
        renderErrors([
            ["Informe seu país"]
        ], "ct-country", "ct-country")

    if (adrress.value == 0)
        renderErrors([
            ["Precisamos do seu endereço"]
        ], "id-address", "id-address")


    if (state.value == 0)
        renderErrors([
            ["Informe seu estado"]
        ], "id-state", "id-state")


    emailErrors(email)

}


phoneNumber.addEventListener('input', function(e) {
    var x = e.target.value.replace(/\D/g, '').match(/(\d{2})(\d{5})(\d{4})/);
    e.target.value = '(' + x[1] + ') ' + x[2] + '-' + x[3];
});