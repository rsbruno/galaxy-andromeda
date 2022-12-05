//converte string em vetor
function strToArray(str) {
    return str.split("")
}

//filtra procurando maiúsculas e devolve um vetor de encontrados
function hasUpperCase(str) {
    let arrStr = strToArray(str);
    return (arrStr.filter(ch => {
        if (ch == ch.toUpperCase()) {
            return ch;
        }
    })).length > 0 ? true : false;
}

//filtra procurando minúsculas e devolve um vetor de encontrados
function hasLowerCase(str) {
    let arrStr = strToArray(str);
    return (arrStr.filter(ch => {
        if (ch == ch.toLowerCase())
            return ch
    })).length > 0 ? true : false;
}

//filtra procurando números e devolve um vetor de encontrados
function hasNumber(str) {
    let arrStr = strToArray(str);
    return (arrStr.filter(ch => {
        if (!isNaN(parseInt(ch)))
            return ch
    })).length > 0 ? true : false;
}