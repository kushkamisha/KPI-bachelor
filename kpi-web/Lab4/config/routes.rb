Rails.application.routes.draw do
  get 'tables/index'

  root 'tables#index'
  
  get "/blog" => "tables#blog"
  get "/why-us" => "tables#why-us"
  get "/photos" => "tables#photos"
  get "/about-us" => "tables#about-us"

  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
