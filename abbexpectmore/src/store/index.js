import Vue from 'vue';
import Vuex from 'vuex';

Vue.use(Vuex)

const store = new Vuex.Store({
  state: {
    products: [
      {name:'Bone Boi £', price: 30},
      {name:'Bone £', price: 290},
      {name:'Bo £', price: 20}
    ]
  },
  mutations: {
  },
  actions: {
  },
  modules: {
  }
})

export default store
