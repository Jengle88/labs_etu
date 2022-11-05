export class Preprocessor {
    static BookStatus = Object.freeze({
        IN_STOCK: "IN_STOCK",
        UNAVAILABLE: "UNAVAILABLE",
        UNKNOWN: "UNKNOWN"
    })

    static statusToLocaleLang(status, returnDate) {
        switch (status) {
            case Preprocessor.BookStatus.IN_STOCK: return "В наличии";
            case Preprocessor.BookStatus.UNAVAILABLE: {
                let nowDateForCompare = new Date(Date.now())
                let returnDateForCompare = new Date(returnDate)
                if (returnDateForCompare < nowDateForCompare)
                    return "Просрочена"
                else
                    return "Занята";
            }
            default: return "Неизвестно";
        }
    }

    static statusFromLocaleLang(status) {
        switch (status) {
            case "В наличии": return Preprocessor.BookStatus.IN_STOCK;
            case "Занята": return Preprocessor.BookStatus.UNAVAILABLE;
            case "Просрочена": return Preprocessor.BookStatus.UNAVAILABLE;
            default: return Preprocessor.BookStatus.UNKNOWN;
        }
    }

}