import React, { useState } from 'react';
import { View, Text, TextInput, TouchableOpacity, StyleSheet, Modal } from 'react-native';
import { BarChart } from 'react-native-chart-kit';
import dados from '../../dataTest/dados15.json';

let color = '#4B9460';

export const HorizontalList = ({ Variavel, Valor, Input }) => {
  const [text, setText] = useState('');
  const handleTextChange = (newText) => {
    const numericText = newText.replace(/[^0-9]/g, '');
    setText(numericText);
  };

  return (
    <View>
      {Input ? (
        <View style={styles.container}>
          <View style={styles.leftContent}>
            <View style={styles.circle}></View>
            <Text style={styles.boldText}>{Variavel}</Text>
          </View>
          <View style={styles.inputContainer}>
            <TextInput
              style={[styles.input, { textAlign: 'center' }]}
              value={text}
              onChangeText={handleTextChange}
              placeholder='1'
              keyboardType="numeric"
            />
            <Text>{Valor}</Text>
          </View>
        </View>
      ) : (
        <View style={styles.container}>
          <View style={styles.leftContent}>
            <View style={styles.circle}></View>
            <Text style={{fontWeight: 'bold'}}>{Variavel}</Text>
          </View>
          <Text>{Valor}</Text>
        </View>
      )}
      <View style={styles.hr}></View>
    </View>

  );
};

export const Chart = (opt) => {
  const data = {
    labels: dados.map((item) => item.label),
    datasets: [{ data: dados.map((item) => item.value) }]
  };
  const xAxisStyle = {
    fontSize: 12,
    transform: [{ rotate: '90deg' }],
    marginLeft: 20,
  };
  const days = [7, 12, 15, 30, 60];
  let percentage = 10.5 / days[opt.opt];
  return (
    <View>
      <BarChart
        data={data}
        width={400}
        height={200}
        yAxisLabel=""
        chartConfig={{
          backgroundGradientFrom: 'white',
          backgroundGradientTo: 'white',
          decimalPlaces: 0,
          color: (opacity = 1) => `rgba(0, 0, 0, ${opacity})`,
          labelColor: (opacity = 1) => `rgba(0, 0, 0, ${opacity})`,
          barPercentage: percentage,
          propsForLabels: {
            fontSize: 8,
          },
        }}
      />
    </View>
  );
};

export const RoundButton = ({ palavra, page }) => {
  let string = '';
  if (page == 'home') string = 'Leitura feita (sqn)';
  else if (page == 'settings') string = 'Configs salvas (sqn)';

  return (
    <View style={styles.roundButtonContainer}>
      <View style={styles.leftContent} />
      <TouchableOpacity
        style={styles.roundButton}
        onPress={() => { alert(string) }}
      >
        <Text style={styles.textRoundButton}>{palavra}</Text>
      </TouchableOpacity>
    </View>
  );
};

export const Disconnected = () =>{
  return(<View><Text>TESTE FUNCIONOU</Text></View>)
}

export const Dropdown = () => {
  const [isDropdownVisible, setIsDropdownVisible] = useState(false);
  const [selectedOption, setSelectedOption] = useState('Opção 1');
  const handleOptionChange = (itemValue) => {
    setSelectedOption(itemValue);
    toggleDropdown();
    console.log(selectedOption);
  };
  const toggleDropdown = () => { setIsDropdownVisible(!isDropdownVisible); };

  return (
    <View style={styles.dropdownContainer}>
      <TouchableOpacity
        style={styles.picker}
        onPress={toggleDropdown}
      >
        <Text style={styles.itemStyle}>{selectedOption}</Text>
      </TouchableOpacity>

      <Modal
        visible={isDropdownVisible}
        transparent={true}
        animationType="slide"
        onRequestClose={toggleDropdown}
      >
        <View style={styles.modalContainer}>
          {['Opção 1', 'Opção 2', 'Opção 3', 'Opção 4', 'Opção 5'].map((option) => (
            <TouchableOpacity
              key={option}
              style={styles.dropdownOption}
              onPress={() => handleOptionChange(option)}
            >
              <Text style={styles.itemStyle}>{option}</Text>
            </TouchableOpacity>
          ))}
        </View>
      </Modal>
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flexDirection: 'row',
    alignItems: 'center',
    justifyContent: 'space-between',
    width: '100%',
    height: 50,
    paddingHorizontal: 10,
    backgroundColor: 'white',
  },
  leftContent: {
    flexDirection: 'row',
    alignItems: 'center',
  },
  circle: {
    width: 18,
    height: 18,
    backgroundColor: color,
    borderRadius: 18 / 1,
    borderColor: 'darkgray',
    borderWidth: 1,
    marginRight: 10,
  },
  hr: {
    width: '95%',
    height: 1,
    backgroundColor: '#E8E8E8',
    alignSelf: 'center',
  },
  inputContainer: {
    flexDirection: 'row',
    alignItems: 'center',
    width: 70
  },
  input: {
    width: 30,
    borderWidth: 1,
    borderColor: 'gray',
    padding: 1,
    fontSize: 18,
  },
  roundButtonContainer: {
    flex: 1,
    flexDirection: 'row',
    alignItems: 'center',
    justifyContent: 'space-between',
    paddingHorizontal: 20,
  },
  roundButton: {
    backgroundColor: '#4B9460',
    borderRadius: 10,
    paddingVertical: 10,
    paddingHorizontal: 20,
    marginTop: 20,
  },
  textRoundButton: {
    color: 'white',
    fontWeight: 'bold',
  },
  dropdownContainer: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
    maxWidth: 150,
    paddingVertical: 10
  },
  picker: {
    borderRadius: 10,
    backgroundColor: color,
  },
  itemStyle: {
    color: 'white',
    paddingVertical: 10,
    paddingHorizontal: 20,
    fontSize: 16,
  },
  modalContainer: {
    flex: 1,
    justifyContent: 'flex-end',
  },
  dropdownOption: {
    backgroundColor: color,
    borderBottomColor: 'white',
    borderBottomWidth: 1,
  },
});

export default styles;