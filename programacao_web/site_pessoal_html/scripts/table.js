//monta as células da tabela ja comm os dados
function renderTable(array, nameElem, page = 1, max = limMax) {
    if (array.length > 0) {
        atualPage = page;
        const html = document.getElementById(nameElem)

        pagesNum = (Math.ceil(array.length / max))

        const teto = (page * max)
        const lim = teto > array.length ? array.length : teto

        for (let i = ((page - 1) * max); i < lim; i++) {
            const node = document.createElement("tr");
            node.id = `${nameElem}-${i}`

            let td = node.insertCell()
            td.appendChild(document.createTextNode(array[i].id));

            td = node.insertCell()
            td.appendChild(document.createTextNode(array[i].phoneNumber));

            td = node.insertCell()
            td.appendChild(document.createTextNode(array[i].firstName));

            td = node.insertCell()
            td.appendChild(document.createTextNode(array[i].lastName));

            td = node.insertCell()
            td.appendChild(document.createTextNode(array[i].emailAddress));

            html.append(node);

        }
        renderProps()
        changeButton(`btn${page}`)
    }
}

//desmonta a tabela
function unMountTable(nameElem) {
    for (let i = ((atualPage - 1) * limMax); i < atualPage * limMax; i++) {
        const html = document.getElementById(`${nameElem}-${i}`)
        if (html)
            html.remove()
    }
}