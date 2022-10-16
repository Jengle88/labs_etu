export class TableRowBook {
    static #createBookTitleAndAuthorDiv(title, author) {
        let bookTitleAndAuthor = document.createElement("div")
        bookTitleAndAuthor.className = "book-title-and-author"
        let bookTitle = document.createElement("p")
        bookTitle.className = "book-title"
        bookTitle.innerText = title
        let bookAuthor = document.createElement("p")
        bookAuthor.className = "book-author"
        bookAuthor.innerText = author
        bookTitleAndAuthor.append(bookTitle, bookAuthor)
        return bookTitleAndAuthor;
    }

    static #createBookStatusAndActionsDiv(status, onclickTakeAction, onclickReturnAction) {
        let bookStatusAndActions = document.createElement("div")
        bookStatusAndActions.className = "book-status-and-actions"
        let bookStatus = document.createElement("p")
        bookStatus.className = "book-status"
        bookStatus.innerText = status
        let bookActionsDiv = document.createElement("div")
        bookActionsDiv.className = "book-actions"
        let takeBookActionImg = document.createElement("img")
        takeBookActionImg.src = "../drawable/ic_add_book.png"
        takeBookActionImg.className = "book-action-icon"
        takeBookActionImg.onclick = onclickTakeAction
        let returnBookActionImg = document.createElement("img")
        returnBookActionImg.src = "../drawable/ic_remove_book.png"
        returnBookActionImg.className = "book-action-icon"
        returnBookActionImg.onclick = onclickReturnAction
        bookActionsDiv.append(takeBookActionImg, returnBookActionImg)
        bookStatusAndActions.append(bookStatus, bookActionsDiv)
        return bookStatusAndActions
    }

    static createBookRow(title, author, status, onclickTakeAction, onclickReturnAction) {
        let newBook = document.createElement("div")
        newBook.className = "book-in-list-of-books"
        let bookTitleAndAuthor = TableRowBook.#createBookTitleAndAuthorDiv(title, author);
        let bookStatusAndActions = TableRowBook.#createBookStatusAndActionsDiv(status, onclickTakeAction, onclickReturnAction)
        newBook.append(bookTitleAndAuthor, bookStatusAndActions)
        return newBook
    }
}

