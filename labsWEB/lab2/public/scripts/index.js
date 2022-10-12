import {
    addBook
} from "./client.js";

let addBookButton = document.getElementById("add_new_book")

addBookButton.addEventListener('click', addBook)