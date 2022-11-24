const roles = Object.freeze({
    "admin": "Администратор",
    "user": "Пользователь",
    "banned": "Заблокированный"
})

const genders = Object.freeze({
    "male": "Мужской",
    "female": "Женский"
})

class StringPreprocessor {
    getUserRole(role) {
        if (role in roles)
            return roles[role]
        else
            return "Undefined"
    }

    getGender(gender) {
        if (gender in genders)
            return genders[gender]
        else
            return "Undefined"
    }
}

const stringPreprocessor = new StringPreprocessor()
function localizeData(user) {
    user.role = stringPreprocessor.getUserRole(user.role)
    user.gender = stringPreprocessor.getGender(user.gender)
    return user
}

module.exports.localizeData = localizeData