import {
    toAddNewBookPage,
    toIndexPage,
} from "./client.js";

// set id
const buttonAddNewBook = document.getElementById("start_add_new_book")
const mainTitle = document.getElementById("main_title")

// set listeners
buttonAddNewBook.addEventListener("click", toAddNewBookPage)
mainTitle.addEventListener("click", toIndexPage)
