import Vue from 'vue';
import Vuex from 'vuex';

Vue.use(Vuex)

const store = new Vuex.Store({
  state: {
    products: [
      {name:'Bone Boi', price: 30},
      {name:'Bone', price: 290},
      {name:'Bo', price: 20}
    ]
  },
  getters:{
    saleProducts: state => {
      var saleProducts = state.products.map(product => {
        return {
            name: product.name,
            price: product.price/2
        }
    })
    return saleProducts
    }
  },
  mutations: {
    reducePrice: (state, payload) => {
      state.products.forEach(product => {
      product.price -= payload
   });         
    }
  },
  //Actions to async
  actions: {
    reducePrice: (context, payload) => {
      setTimeout(function(){
        context.commit('reducePrice', payload)
      },2000)
    }
  },
  modules: {
  }
})

export default store
