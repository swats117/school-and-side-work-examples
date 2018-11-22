import { StyleSheet } from 'react-native';
import constants from "./global-constants";
// const win = Dimensions.get('window');
module.exports = StyleSheet.create({
  video_player:{
    width:300,
    height: 300
  },
  controlBar: {
    position: 'absolute',
    bottom: 0,
    left: 0,
    right: 0,
    height: "100%",
    flexDirection: 'row',
    alignItems: 'stretch',
    justifyContent: 'center',
    backgroundColor: "rgba(0, 0, 0, 0.5)",
  },
  container: {
    flex: 1,
    backgroundColor: '#F5FCFF',
  },
  centered_container:{
    flex: 1,
    backgroundColor: "rgba(0, 0, 0, 0.5)",
    justifyContent: 'center',
  },
  double_container: {
    flex: 2,
  },
  image_style: {
    flex: 1,
  },
  fields_style: {
    alignItems: 'flex-start',
    flex: 2,
    width: "70%",
    paddingLeft:"15%"
  },
  flex1: {
    flex: 1,
  },
  flex2: {
    flex: 2,
  },
  tab_bar_style: {
    height: 20,
    width: '100%',
  },
  welcome: {
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
  },
  instructions: {
    textAlign: 'center',
    color: '#333333',
    marginBottom: 5,
  },
  contentContainer: {
    paddingVertical: 20
  },
  borderSeparator:{
    height: 4,
    width: '100%',
    backgroundColor: '#909090',
  },
  canvas: {
    position: 'absolute',
    top: 0,
    left: 0,
    bottom: 0,
    right: 0,
  }
});