let pagesNum = 0,
    atualPage = 1,
    guests = [],
    filtered = [],
    limMax = 10


//importa os dados
//em caso de usar outra API é só carregar os dados aqui
async function buscar() {
    const response = await fetch("../scripts/utils/guests.json")
    const guests = await response.json()
    return guests
}

//filtra os guests com a entrada do usuário
function search(event) {
    const filter = event.value.toLowerCase()
    filtered = guests.filter(e => {
        if (e.firstName.toLowerCase().includes(filter))
            return true;
        if (e.lastName.toLowerCase().includes(filter))
            return true;
        if (e.phoneNumber.includes(filter))
            return true;
        if (e.emailAddress.toLowerCase().includes(filter))
            return true;
    })
    unMountTable("teste")
    unMountControls()
    renderTable(filtered, "teste", atualPage, limMax)
    renderButtons("controls", pagesNum, atualPage)
}

//start usando async e await  
async function main() {
    guests = await buscar()
    renderTable(guests, "teste", 1, limMax)
    renderButtons("controls", pagesNum, atualPage)
}
//main() //descomentar e comentar a promisse para usar async e await

//start usando promisse
const fetchPromise = fetch("../scripts/utils/guests.json");
fetchPromise.then(response => {
    return response.json();
}).then(people => {
    guests = people
    renderTable(guests, "teste", 1, limMax)
    renderButtons("controls", pagesNum, atualPage)
});

/*
 ** da forma como esta a aplicação estaáusando promisse
 */