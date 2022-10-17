import {
    toAddNewBookPage,
} from "./client.js";

// set id
const buttonAddNewBook = document.getElementById("start_add_new_book")

// set listeners
buttonAddNewBook.addEventListener("click", toAddNewBookPage)

