path = "C:/Users/Brendan van Walstijn/Documents/Power Monitoring/SavedData.txt"


def filter_content(content):
    sentence = str(content)

    # split at backslash
    sentence_list = sentence.split('\\')
    for word in sentence_list:
        if 'nVoltage' in word:
            voltage_final_sentence = word.split(' ')
            # string_to_append.append('c ' + voltage_final_sentence[1] + ' ' + identifier + ' ')

            f = open(path, 'a')
            f.write('c ' + voltage_final_sentence[1] +'\n')
            f.close()

        if 'nPower_usage' in word:
            power_final_sentence = word.split(' ')
            # string_to_append.append('p ' + power_final_sentence[1] + ' ' + identifier + '\n')

            f = open(path,'a')
            f.write('p ' + power_final_sentence[1] + '\n')
            f.write('\n')
            f.close()
