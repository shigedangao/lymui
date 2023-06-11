use napi::bindgen_prelude::*;

pub trait FromJsObject {
    fn from_js_object(object: Object) -> Result<Self>
    where
        Self: Sized;
}

pub trait IntoJsObject {
    fn into_js_object(&self, env: Env) -> Result<Object>;
}

pub mod prelude {
    pub use super::{FromJsObject, IntoJsObject};
    pub use js_macro::{FromJsObj, IntoJsObject};
    pub use napi::bindgen_prelude::{Object, Result as NapiResult, Status, Env};
    pub use napi::Error as JsError;
}
