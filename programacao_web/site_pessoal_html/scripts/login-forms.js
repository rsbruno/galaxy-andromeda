function changeType() {
    const elem = document.getElementById("password")
    const eye = document.getElementById("eye")

    if (elem.type == "password") {
        eye.classList.remove("fa-eye")
        eye.classList.add("fa-eye-slash")
        elem.type = "text"
    } else {
        eye.classList.remove("fa-eye-slash")
        eye.classList.add("fa-eye")
        elem.type = "password"
    }
}

function validateForm() {

    const idUser = "usr"
    const idPass = "pass"

    removeErrors(idUser)
    removeErrors(idPass)

    const [userErrors] = formUser("username")
    const [passErrors] = formPassword("password");

    renderErrors(userErrors, "container-user", idUser)
    renderErrors(passErrors, "container-pass", idPass)

}

function formUser(element) {
    const input = document.getElementById(element)
    const value = input.value
    const errors = []

    if (value.length == 0)
        return [
            ["Você precisa informar seu usuário"]
        ]

    return [
        []
    ]
}

function formPassword(element) {
    const input = document.getElementById(element)
    const value = input.value
    const errors = []

    //em caso de campo vazio não deve comparar o restante dos erros
    if (value.length == 0)
        return [
            ["Você precisa informar sua senha"]
        ]

    //se chegamos aqui o campo não está vazio e podemos aplicar as regras
    if (value.length < 8) errors.push("Necessário ter no mínimo 8 caracteres")
    if (!hasUpperCase(value)) errors.push("Necessário pelo menos uma letra Maiúscula")
    if (!hasLowerCase(value)) errors.push("Necessário pelo menos uma letra Minúscula")
    if (!hasNumber(value)) errors.push("Necessário pelo menos um número")

    return [errors]
}