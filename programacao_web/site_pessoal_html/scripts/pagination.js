//define quantos dados serão exibidos em tela
function showDataCount() {
    const count = document.getElementById("counts")
    unMountTable("teste")

    limMax = parseInt(count.value)

    unMountControls()

    renderTable(filtered.length > 0 ? filtered : guests, "teste", atualPage, limMax)

    renderButtons("controls", pagesNum, atualPage)
}

//funçã anterior
function previous() {
    if (atualPage != 1) {
        unMountTable("teste")
        renderTable(filtered.length > 0 ? filtered : guests, "teste", atualPage - 1, limMax)
    }
}

//função próximo
function next() {
    if (atualPage < pagesNum) {
        unMountTable("teste")
        renderTable(filtered.length > 0 ? filtered : guests, "teste", atualPage + 1, limMax)
    }
}

//renderiza as propriedades no footer da tabelas
function renderProps() {
    document.getElementById("atual-page").innerHTML = `${(atualPage * limMax) - (limMax - 1)}`
    document.getElementById("limit").innerHTML = `${limMax}`
    document.getElementById("total").innerHTML = `${filtered.length > 0 ? filtered.length : guests.length}`
}

//define qual pagina esta ativa e aplica um css diferente nos botões
function changeButton(btn) {
    const hasClass = document.getElementsByClassName("is-actived")
    if (hasClass.length > 0)
        hasClass[0].classList.remove("is-actived")
    const button = document.getElementById(btn)
    if (button)
        button.classList.add("is-actived")
}

//desmonta os botões de paginação
function unMountControls() {
    for (let i = 1; i <= pagesNum; i++) {
        const button = document.getElementById(`btn${i}`)
        if (button)
            button.remove()
    }
}

//renderiza os botões de paginção
function renderButtons(nameElem, qndt, atualPage) {
    for (let i = 1; i <= qndt; i++) {
        const html = document.getElementById(nameElem)
        const node = document.createElement("button");
        node.id = `btn${i}`
        node.onclick = function() {
            unMountTable("teste")
            renderTable(filtered.length > 0 ? filtered : guests, "teste", i, limMax)
        };
        var textnode = document.createTextNode(i);

        node.appendChild(textnode);
        html.append(node);

    }
    changeButton(`btn${atualPage}`)
}