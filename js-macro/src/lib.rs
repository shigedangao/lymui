use proc_macro::TokenStream;
use quote::quote;
use syn::{Data, DeriveInput};

#[proc_macro_derive(FromJsObj)]
pub fn from_js_object(input: TokenStream) -> TokenStream {
    let input: DeriveInput = syn::parse_macro_input!(input);
    let name = input.ident;

    let Data::Struct(struct_data) = input.data else {
        unimplemented!("Supporting only struct");
    };

    let de_fields = struct_data
        .fields
        .iter()
        .map(|field| match field.ident.as_ref() {
            Some(ident) => {
                quote! {
                    #ident : object.get(stringify!(#ident))
                        .and_then(|v| v.ok_or(JsError::from_status(Status::InvalidArg)))?,
                }
            }
            None => {
                quote! {
                    0 : object.get(stringify!(0))
                        .and_then(|v| v.ok_or(JsError::from_status(Status::InvalidArg)))?,
                }
            }
        });

    let expanded = quote! {
        #[automatically_derived]
        impl FromJsObject for #name {
            fn from_js_object(object: Object) -> NapiResult<Self> {
                Ok(Self {
                    #( #de_fields )*
                })
            }
        }
    };

    TokenStream::from(expanded)
}

#[proc_macro_derive(IntoJsObject)]
pub fn into_js_object(input: TokenStream) -> TokenStream {
    let input: DeriveInput = syn::parse_macro_input!(input);
    let name = input.ident;

    let Data::Struct(struct_data) = input.data else {
        unimplemented!("Supporting only struct");
    };

    let se_fields = struct_data
        .fields
        .iter()
        .map(|field| match field.ident.as_ref() {
            Some(ident) => {
                quote! {
                    res.set(stringify!(#ident), self.#ident)?;
                }
            }
            None => {
                quote! {
                    res.set(stringify!(0), self.0.clone())?;
                }
            }
        });

    let expanded = quote! {
        #[automatically_derived]
        impl IntoJsObject for #name {
            fn into_js_object(&self, env: Env) -> NapiResult<Object> {
                let mut res = env.create_object()?;
                #( #se_fields )*

                Ok(res)
            }
        }
    };

    TokenStream::from(expanded)
}
