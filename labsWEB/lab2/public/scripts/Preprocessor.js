export class Preprocessor {
    static BookStatus = Object.freeze({
        IN_STOCK: "IN_STOCK",
        UNAVAILABLE: "UNAVAILABLE",
        OVERDUE: "OVERDUE",
        UNKNOWN: "UNKNOWN"
    })

    static statusToLocaleLang(status) {
        switch (status) {
            case Preprocessor.BookStatus.IN_STOCK: return "В наличии";
            case Preprocessor.BookStatus.UNAVAILABLE: return "Занята";
            case Preprocessor.BookStatus.OVERDUE: return "Просрочена";
            default: return "Неизвестно";
        }
    }

    static statusFromLocaleLang(status) {
        switch (status) {
            case "В наличии": return Preprocessor.BookStatus.IN_STOCK;
            case "Занята": return Preprocessor.BookStatus.UNAVAILABLE;
            case "Просрочена": return Preprocessor.BookStatus.OVERDUE;
            default: return Preprocessor.BookStatus.UNKNOWN;
        }
    }
}