import {
    toIndexPage,
    editBook,
    removeBook
} from "./client.js";
import {Preprocessor} from "./Preprocessor.js";
import {Book} from "./Book.js";

const mainTitle = document.getElementById("main_title")

const takeBookButton = document.getElementById("book_info_take_book_button")
const returnBookButton = document.getElementById("book_info_return_book_button")
const editInfoButton = document.getElementById("book_info_edit_info_button")
const deleteBookButton = document.getElementById("book_info_delete_book_button")

const bookTitleInput = document.getElementById("book_info_item_book_title_input")
const bookAuthorInput = document.getElementById("book_info_item_book_author_input")
const bookStatusSelect = document.getElementById("book_info_item_book_status_select")
const bookReleaseDateInput = document.getElementById("book_info_item_book_release_date_input")
const bookWasTakenByInput = document.getElementById("book_info_item_book_was_taken_by_input")
const bookReturnDateInput = document.getElementById("book_info_item_book_return_date_input")

const bookTitleText = document.getElementById("book_info_item_book_title")
const bookAuthorText = document.getElementById("book_info_item_book_author")
const bookStatusText = document.getElementById("book_info_item_book_status")
const bookReleaseDateText = document.getElementById("book_info_item_book_release_date")
const bookWasTakenByText = document.getElementById("book_info_item_book_was_taken_by")
const bookReturnDateText = document.getElementById("book_info_item_book_return_date")

let isEditingMode = false

mainTitle.addEventListener("click", toIndexPage)

editInfoButton.addEventListener("click", () => {
    if (isEditingMode) {
        extractInfoFromInputsToText();
        changeInputsDisplay("none");
        changeTextDisplay("flex");
        let id = document.URL.slice(document.URL.lastIndexOf("/")+1, document.URL.length)
        let book = new Book(
            Number(id),
            bookTitleText.innerText,
            bookAuthorText.innerText,
            Preprocessor.statusFromLocaleLang(bookStatusText.innerText),
            bookReleaseDateText.innerText,
            bookWasTakenByText.innerText,
            bookReturnDateText.innerText
        )
        editBook(book);
    } else {
        extractInfoFromTextToInput();
        changeInputsDisplay("flex");
        changeTextDisplay("none");
    }
    isEditingMode = !isEditingMode
})

deleteBookButton.addEventListener("click", () => {
    let confirmDelete = confirm("Вы уверены, что хотите удалить книгу?")
    if (confirmDelete) {
        let id = document.URL.slice(document.URL.lastIndexOf("/")+1, document.URL.length)
        removeBook(Number(id))
    }
})


function extractInfoFromInputsToText() {
    bookTitleText.innerText = bookTitleInput.value
    bookAuthorText.innerText = bookAuthorInput.value
    bookStatusText.innerText = Preprocessor.statusToLocaleLang(bookStatusSelect.value)
    bookReleaseDateText.innerText = bookReleaseDateInput.value
    bookWasTakenByText.innerText = bookWasTakenByInput.value
    bookReturnDateText.innerText = bookReturnDateInput.value
}

function extractInfoFromTextToInput() {
    bookTitleInput.value = bookTitleText.innerText
    bookAuthorInput.value = bookAuthorText.innerText
    bookStatusSelect.options.selectedIndex = Array.prototype.slice.call(bookStatusSelect.options).findIndex((status) => {
        return Preprocessor.statusFromLocaleLang(bookStatusText.innerText) === status.value
    })
    bookReleaseDateInput.value = bookReleaseDateText.innerText
    bookWasTakenByInput.value = bookWasTakenByText.innerText
    bookReturnDateInput.value = bookReturnDateText.innerText
}

function changeInputsDisplay(displayParams) {
    bookTitleInput.style.display = displayParams
    bookAuthorInput.style.display = displayParams
    bookStatusSelect.style.display = displayParams
    bookReleaseDateInput.style.display = displayParams
    bookWasTakenByInput.style.display = displayParams
    bookReturnDateInput.style.display = displayParams
}

function changeTextDisplay(displayParams) {
    bookTitleText.style.display = displayParams
    bookAuthorText.style.display = displayParams
    bookStatusText.style.display = displayParams
    bookReleaseDateText.style.display = displayParams
    bookWasTakenByText.style.display = displayParams
    bookReturnDateText.style.display = displayParams
}

